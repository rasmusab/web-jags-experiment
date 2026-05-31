#include <Console.h>
#include <sarray/Range.h>
#include <sarray/SArray.h>
#include <util/nainf.h>

#include <cmath>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define JAGS_WASM_EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define JAGS_WASM_EXPORT
#endif

namespace {

struct Runtime {
    std::ostringstream out;
    std::ostringstream err;
    jags::Console console;
    std::map<std::string, jags::SArray> data;
    std::string last_error;
    std::string last_result;

    Runtime() : out(), err(), console(out, err), data(),
		last_error(), last_result()
    {
    }

    void clearMessages()
    {
	out.str("");
	out.clear();
	err.str("");
	err.clear();
	last_error.clear();
    }

    bool finish(bool ok)
    {
	if (!ok) {
	    last_error = err.str();
	    if (last_error.empty()) {
		last_error = out.str();
	    }
	}
	else if (!err.str().empty()) {
	    last_error = err.str();
	}
	return ok;
    }
};

Runtime *asRuntime(void *handle)
{
    return static_cast<Runtime *>(handle);
}

bool loadDefaultModules(std::string &error)
{
    bool ok = jags::Console::loadModule("basemod");
    ok = jags::Console::loadModule("bugs") && ok;
    if (!ok) {
	error = "Failed to load statically linked JAGS modules";
    }
    return ok;
}

std::string escapeJson(std::string const &value)
{
    std::ostringstream out;
    for (std::string::const_iterator p = value.begin(); p != value.end(); ++p) {
	switch (*p) {
	case '"':
	    out << "\\\"";
	    break;
	case '\\':
	    out << "\\\\";
	    break;
	case '\b':
	    out << "\\b";
	    break;
	case '\f':
	    out << "\\f";
	    break;
	case '\n':
	    out << "\\n";
	    break;
	case '\r':
	    out << "\\r";
	    break;
	case '\t':
	    out << "\\t";
	    break;
	default:
	    out << *p;
	    break;
	}
    }
    return out.str();
}

void appendArrayJson(std::ostringstream &out, jags::SArray const &array)
{
    out << "{\"dim\":[";
    std::vector<unsigned int> const &dim = array.dim(false);
    for (unsigned int i = 0; i < dim.size(); ++i) {
	if (i != 0) {
	    out << ',';
	}
	out << dim[i];
    }

    out << "],\"values\":[";
    std::vector<double> const &values = array.value();
    for (unsigned int i = 0; i < values.size(); ++i) {
	if (i != 0) {
	    out << ',';
	}
	if (values[i] == JAGS_NA || jags_isnan(values[i])) {
	    out << "null";
	}
	else if (jags_finite(values[i])) {
	    out << values[i];
	}
	else {
	    out << "null";
	}
    }
    out << "]}";
}

std::vector<double> normalizeMissing(double const *values, unsigned int length)
{
    std::vector<double> normalized(values, values + length);
    for (unsigned int i = 0; i < normalized.size(); ++i) {
	if (jags_isnan(normalized[i])) {
	    normalized[i] = JAGS_NA;
	}
    }
    return normalized;
}

int fail(Runtime *runtime, std::string const &message)
{
    if (runtime) {
	runtime->last_error = message;
    }
    return 0;
}

} // namespace

extern "C" {

JAGS_WASM_EXPORT void *jags_create()
{
    Runtime *runtime = new Runtime;
    std::string error;
    if (!loadDefaultModules(error)) {
	runtime->last_error = error;
    }
    return runtime;
}

JAGS_WASM_EXPORT void jags_destroy(void *handle)
{
    delete asRuntime(handle);
}

JAGS_WASM_EXPORT char const *jags_last_error(void *handle)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return "Invalid JAGS runtime handle";
    }
    return runtime->last_error.c_str();
}

JAGS_WASM_EXPORT int jags_set_seed(unsigned int seed)
{
    jags::Console::setRNGSeed(seed);
    return 1;
}

JAGS_WASM_EXPORT int jags_check_model(void *handle, char const *model_text)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    if (!model_text) {
	return fail(runtime, "Model text is null");
    }

    runtime->clearMessages();
    try {
	return runtime->finish(runtime->console.checkModel(std::string(model_text))) ? 1 : 0;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT int jags_clear_data(void *handle)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    runtime->data.clear();
    runtime->last_error.clear();
    return 1;
}

JAGS_WASM_EXPORT int jags_set_data(void *handle, char const *name,
				   unsigned int const *dims,
				   unsigned int ndim,
				   double const *values,
				   unsigned int length)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    if (!name || !dims || !values || ndim == 0 || length == 0) {
	return fail(runtime, "Invalid data array");
    }

    try {
	std::vector<unsigned int> dim(dims, dims + ndim);
	unsigned int expected = 1;
	for (unsigned int i = 0; i < dim.size(); ++i) {
	    if (dim[i] == 0) {
		return fail(runtime, "Data dimensions must be positive");
	    }
	    expected *= dim[i];
	}
	if (expected != length) {
	    return fail(runtime, "Data length does not match dimensions");
	}

	jags::SArray array(dim);
	array.setValue(normalizeMissing(values, length));
	runtime->data.erase(name);
	runtime->data.insert(std::map<std::string, jags::SArray>::value_type(name, array));
	runtime->last_error.clear();
	return 1;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT int jags_set_parameter(void *handle, unsigned int chain,
					char const *name,
					unsigned int const *dims,
					unsigned int ndim,
					double const *values,
					unsigned int length)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    if (!name || !dims || !values || ndim == 0 || length == 0) {
	return fail(runtime, "Invalid parameter array");
    }

    try {
	std::vector<unsigned int> dim(dims, dims + ndim);
	unsigned int expected = 1;
	for (unsigned int i = 0; i < dim.size(); ++i) {
	    if (dim[i] == 0) {
		return fail(runtime, "Parameter dimensions must be positive");
	    }
	    expected *= dim[i];
	}
	if (expected != length) {
	    return fail(runtime, "Parameter length does not match dimensions");
	}

	jags::SArray array(dim);
	array.setValue(normalizeMissing(values, length));
	std::map<std::string, jags::SArray> init_table;
	init_table.insert(std::map<std::string, jags::SArray>::value_type(name, array));

	runtime->clearMessages();
	return runtime->finish(runtime->console.setParameters(init_table, chain)) ? 1 : 0;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT int jags_compile(void *handle, unsigned int nchain,
				  int generate_data)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    runtime->clearMessages();
    try {
	return runtime->finish(runtime->console.compile(runtime->data, nchain,
							generate_data != 0)) ? 1 : 0;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT int jags_initialize(void *handle)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    runtime->clearMessages();
    try {
	return runtime->finish(runtime->console.initialize()) ? 1 : 0;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT int jags_adapt_off(void *handle)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    runtime->clearMessages();
    try {
	return runtime->finish(runtime->console.adaptOff()) ? 1 : 0;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT int jags_update(void *handle, unsigned int niter)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    runtime->clearMessages();
    try {
	return runtime->finish(runtime->console.update(niter)) ? 1 : 0;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT int jags_set_monitor(void *handle, char const *name,
				      unsigned int thin, char const *type)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    if (!name) {
	return fail(runtime, "Monitor name is null");
    }

    runtime->clearMessages();
    try {
	std::string monitor_type = type && *type ? type : "trace";
	return runtime->finish(runtime->console.setMonitor(name, jags::Range(),
							   thin, monitor_type)) ? 1 : 0;
    }
    catch (std::exception const &ex) {
	return fail(runtime, ex.what());
    }
}

JAGS_WASM_EXPORT char const *jags_dump_monitors(void *handle, char const *type,
					       int flat)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return "";
    }

    runtime->clearMessages();
    try {
	std::map<std::string, jags::SArray> monitors;
	std::string monitor_type = type && *type ? type : "trace";
	if (!runtime->finish(runtime->console.dumpMonitors(monitors, monitor_type,
							   flat != 0))) {
	    return "";
	}

	std::ostringstream out;
	out << '{';
	bool first = true;
	for (std::map<std::string, jags::SArray>::const_iterator p = monitors.begin();
	     p != monitors.end(); ++p) {
	    if (!first) {
		out << ',';
	    }
	    first = false;
	    out << '"' << escapeJson(p->first) << "\":";
	    appendArrayJson(out, p->second);
	}
	out << '}';
	runtime->last_result = out.str();
	return runtime->last_result.c_str();
    }
    catch (std::exception const &ex) {
	fail(runtime, ex.what());
	return "";
    }
}

JAGS_WASM_EXPORT char const *jags_parameter_names(void *handle)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return "[]";
    }

    runtime->clearMessages();
    try {
	std::map<std::string, jags::SArray> state;
	std::string rng_name;
	if (!runtime->finish(runtime->console.dumpState(state, rng_name,
							jags::DUMP_PARAMETERS, 1))) {
	    return "[]";
	}

	std::ostringstream out;
	out << '[';
	bool first = true;
	for (std::map<std::string, jags::SArray>::const_iterator p = state.begin();
	     p != state.end(); ++p) {
	    if (p->first == ".RNG.state" || p->first == ".RNG.name") {
		continue;
	    }
	    if (!first) {
		out << ',';
	    }
	    first = false;
	    out << '"' << escapeJson(p->first) << '"';
	}
	out << ']';
	runtime->last_result = out.str();
	return runtime->last_result.c_str();
    }
    catch (std::exception const &ex) {
	fail(runtime, ex.what());
	return "[]";
    }
}

JAGS_WASM_EXPORT unsigned int jags_iteration(void *handle)
{
    Runtime *runtime = asRuntime(handle);
    if (!runtime) {
	return 0;
    }
    return runtime->console.iter();
}

} // extern "C"
