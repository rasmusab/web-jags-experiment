#include <config.h>

#include <algorithm>
#include <cmath>
#include <vector>

namespace {

inline int idx(int row, int col, int ld)
{
    return row + col * ld;
}

inline void set_info(const int *info, int value)
{
    *const_cast<int *>(info) = value;
}

double tri_value(const double *a, int lda, bool upper, bool unit,
		 bool trans, int row, int col)
{
    int source_row = trans ? col : row;
    int source_col = trans ? row : col;
    if (source_row == source_col && unit) {
	return 1.0;
    }
    if ((upper && source_row <= source_col) ||
	(!upper && source_row >= source_col)) {
	return a[idx(source_row, source_col, lda)];
    }
    return 0.0;
}

bool cholesky_lower(double *a, int n, int lda)
{
    for (int col = 0; col < n; ++col) {
	double sum = a[idx(col, col, lda)];
	for (int k = 0; k < col; ++k) {
	    double v = a[idx(col, k, lda)];
	    sum -= v * v;
	}
	if (sum <= 0 || !std::isfinite(sum)) {
	    return false;
	}
	a[idx(col, col, lda)] = std::sqrt(sum);
	for (int row = col + 1; row < n; ++row) {
	    double value = a[idx(row, col, lda)];
	    for (int k = 0; k < col; ++k) {
		value -= a[idx(row, k, lda)] * a[idx(col, k, lda)];
	    }
	    a[idx(row, col, lda)] = value / a[idx(col, col, lda)];
	}
    }
    for (int row = 0; row < n; ++row) {
	for (int col = row + 1; col < n; ++col) {
	    a[idx(row, col, lda)] = 0.0;
	}
    }
    return true;
}

void invert_triangular(const char *uplo, const char *diag, const int *n,
		       double *a, const int *lda, const int *info)
{
    bool upper = *uplo == 'U' || *uplo == 'u';
    bool unit = *diag == 'U' || *diag == 'u';
    int N = *n;
    std::vector<double> inv(N * N, 0.0);

    if (upper) {
	for (int col = 0; col < N; ++col) {
	    for (int row = N - 1; row >= 0; --row) {
		double sum = row == col ? 1.0 : 0.0;
		for (int k = row + 1; k < N; ++k) {
		    sum -= tri_value(a, *lda, true, unit, false, row, k) *
			inv[idx(k, col, N)];
		}
		double diag_value = unit ? 1.0 : a[idx(row, row, *lda)];
		if (diag_value == 0.0) {
		    set_info(info, row + 1);
		    return;
		}
		inv[idx(row, col, N)] = sum / diag_value;
	    }
	}
    }
    else {
	for (int col = 0; col < N; ++col) {
	    for (int row = 0; row < N; ++row) {
		double sum = row == col ? 1.0 : 0.0;
		for (int k = 0; k < row; ++k) {
		    sum -= tri_value(a, *lda, false, unit, false, row, k) *
			inv[idx(k, col, N)];
		}
		double diag_value = unit ? 1.0 : a[idx(row, row, *lda)];
		if (diag_value == 0.0) {
		    set_info(info, row + 1);
		    return;
		}
		inv[idx(row, col, N)] = sum / diag_value;
	    }
	}
    }

    for (int col = 0; col < N; ++col) {
	for (int row = 0; row < N; ++row) {
	    a[idx(row, col, *lda)] = inv[idx(row, col, N)];
	}
    }
    set_info(info, 0);
}

} // namespace

extern "C" {

double F77_FUNC(ddot, DDOT)(const int *n, double const *x, const int *incx,
			    double const *y, const int *incy)
{
    double ans = 0;
    for (int i = 0; i < *n; ++i) {
	ans += x[i * *incx] * y[i * *incy];
    }
    return ans;
}

void F77_FUNC(dcopy, DCOPY)(const int *n, double const *x, const int *incx,
			    double *y, const int *incy)
{
    for (int i = 0; i < *n; ++i) {
	y[i * *incy] = x[i * *incx];
    }
}

void F77_FUNC(dscal, DSCAL)(const int *n, double const *alpha, double *x,
			    const int *incx)
{
    for (int i = 0; i < *n; ++i) {
	x[i * *incx] *= *alpha;
    }
}

void F77_FUNC(daxpy, DAXPY)(const int *n, const double *alpha,
			    const double *x, const int *incx, double *y,
			    const int *incy)
{
    for (int i = 0; i < *n; ++i) {
	y[i * *incy] += *alpha * x[i * *incx];
    }
}

void F77_FUNC(dgemv, DGEMV)(const char *trans, const int *m, const int *n,
			    const double *alpha, const double *a,
			    const int *lda, const double *x,
			    const int *incx, const double *beta,
			    double *y, const int *incy)
{
    bool t = *trans == 'T' || *trans == 't';
    int rows = t ? *n : *m;
    int inner = t ? *m : *n;
    for (int i = 0; i < rows; ++i) {
	double sum = 0;
	for (int j = 0; j < inner; ++j) {
	    double av = t ? a[j + i * *lda] : a[i + j * *lda];
	    sum += av * x[j * *incx];
	}
	y[i * *incy] = *alpha * sum + *beta * y[i * *incy];
    }
}

void F77_FUNC(dgemm, DGEMM)(const char *transa, const char *transb,
			    const int *m, const int *n, const int *k,
			    const double *alpha, const double *a,
			    const int *lda, const double *b,
			    const int *ldb, const double *beta,
			    double *c, const int *ldc)
{
    bool ta = *transa == 'T' || *transa == 't';
    bool tb = *transb == 'T' || *transb == 't';
    for (int col = 0; col < *n; ++col) {
	for (int row = 0; row < *m; ++row) {
	    double sum = 0;
	    for (int inner = 0; inner < *k; ++inner) {
		double av = ta ? a[inner + row * *lda] : a[row + inner * *lda];
		double bv = tb ? b[col + inner * *ldb] : b[inner + col * *ldb];
		sum += av * bv;
	    }
	    c[row + col * *ldc] = *alpha * sum + *beta * c[row + col * *ldc];
	}
    }
}

void F77_FUNC(dsyr, DSYR)(const char *uplo, const int *n, const double *alpha,
			  const double *x, const int *incx, double *a,
			  const int *lda)
{
    bool upper = *uplo == 'U' || *uplo == 'u';
    for (int col = 0; col < *n; ++col) {
	for (int row = 0; row < *n; ++row) {
	    if ((upper && row <= col) || (!upper && row >= col)) {
		a[row + col * *lda] += *alpha * x[row * *incx] * x[col * *incx];
	    }
	}
    }
}

void F77_FUNC(dsymm, DSYMM)(const char *side, const char *, const int *m,
			    const int *n, const double *alpha,
			    const double *a, const int *lda,
			    const double *b, const int *ldb,
			    const double *beta, double *c, const int *ldc)
{
    bool left = *side == 'L' || *side == 'l';
    for (int col = 0; col < *n; ++col) {
	for (int row = 0; row < *m; ++row) {
	    double sum = 0;
	    int inner_count = left ? *m : *n;
	    for (int inner = 0; inner < inner_count; ++inner) {
		double av = left ? a[row + inner * *lda] : a[inner + col * *lda];
		double bv = left ? b[inner + col * *ldb] : b[row + inner * *ldb];
		sum += av * bv;
	    }
	    c[row + col * *ldc] = *alpha * sum + *beta * c[row + col * *ldc];
	}
    }
}

void F77_FUNC(dsyrk, DSYRK)(const char *uplo, const char *trans, const int *n,
			    const int *k, const double *alpha,
			    const double *a, const int *lda,
			    const double *beta, double *c, const int *ldc)
{
    bool upper = *uplo == 'U' || *uplo == 'u';
    bool t = *trans == 'T' || *trans == 't';
    for (int col = 0; col < *n; ++col) {
	for (int row = 0; row < *n; ++row) {
	    if ((upper && row <= col) || (!upper && row >= col)) {
		double sum = 0;
		for (int inner = 0; inner < *k; ++inner) {
		    double ar = t ? a[inner + row * *lda] : a[row + inner * *lda];
		    double ac = t ? a[inner + col * *lda] : a[col + inner * *lda];
		    sum += ar * ac;
		}
		c[row + col * *ldc] = *alpha * sum + *beta * c[row + col * *ldc];
	    }
	}
    }
}

double F77_FUNC(dlange, DLANGE)(const char *norm, const int *m, const int *n,
				const double *a, const int *lda, double *)
{
    double ans = 0;
    if (*norm == '1' || *norm == 'O' || *norm == 'o') {
	for (int col = 0; col < *n; ++col) {
	    double sum = 0;
	    for (int row = 0; row < *m; ++row) {
		sum += std::fabs(a[row + col * *lda]);
	    }
	    ans = std::max(ans, sum);
	}
    }
    else {
	for (int row = 0; row < *m; ++row) {
	    double sum = 0;
	    for (int col = 0; col < *n; ++col) {
		sum += std::fabs(a[row + col * *lda]);
	    }
	    ans = std::max(ans, sum);
	}
    }
    return ans;
}

void F77_FUNC(dtrmm, DTRMM)(const char *side, const char *uplo,
			    const char *transa, const char *diag,
			    const int *m, const int *n,
			    const double *alpha, const double *a,
			    const int *lda, double *b, const int *ldb)
{
    bool left = *side == 'L' || *side == 'l';
    bool upper = *uplo == 'U' || *uplo == 'u';
    bool trans = *transa == 'T' || *transa == 't';
    bool unit = *diag == 'U' || *diag == 'u';
    std::vector<double> out((*m) * (*n));
    for (int col = 0; col < *n; ++col) {
	for (int row = 0; row < *m; ++row) {
	    double sum = 0.0;
	    if (left) {
		for (int k = 0; k < *m; ++k) {
		    sum += tri_value(a, *lda, upper, unit, trans, row, k) *
			b[idx(k, col, *ldb)];
		}
	    }
	    else {
		for (int k = 0; k < *n; ++k) {
		    sum += b[idx(row, k, *ldb)] *
			tri_value(a, *lda, upper, unit, trans, k, col);
		}
	    }
	    out[idx(row, col, *m)] = *alpha * sum;
	}
    }
    for (int col = 0; col < *n; ++col) {
	for (int row = 0; row < *m; ++row) {
	    b[idx(row, col, *ldb)] = out[idx(row, col, *m)];
	}
    }
}

void F77_FUNC(dsyev, DSYEV)(const char *jobz, const char *uplo, const int *n,
			    double *a, const int *lda, double *w, double *work,
			    const int *lwork, int *info)
{
    int N = *n;
    if (*lwork == -1) {
	work[0] = std::max(1, 3 * N - 1);
	*info = 0;
	return;
    }
    if (N < 0) {
	*info = -3;
	return;
    }
    if (N == 0) {
	*info = 0;
	return;
    }

    bool upper = *uplo == 'U' || *uplo == 'u';
    bool vectors = *jobz == 'V' || *jobz == 'v';
    std::vector<double> mat(N * N);
    std::vector<double> vec(N * N, 0.0);
    for (int col = 0; col < N; ++col) {
	vec[idx(col, col, N)] = 1.0;
	for (int row = 0; row < N; ++row) {
	    if ((upper && row <= col) || (!upper && row >= col)) {
		mat[idx(row, col, N)] = a[idx(row, col, *lda)];
	    }
	    else {
		mat[idx(row, col, N)] = a[idx(col, row, *lda)];
	    }
	}
    }

    double norm = 0.0;
    for (double value : mat) {
	norm = std::max(norm, std::fabs(value));
    }
    double tolerance = std::max(1.0, norm) * 1e-12;
    int max_iterations = std::max(32, 64 * N * N);
    bool converged = false;

    for (int iteration = 0; iteration < max_iterations; ++iteration) {
	int p = 0;
	int q = 1;
	double largest = 0.0;
	for (int col = 1; col < N; ++col) {
	    for (int row = 0; row < col; ++row) {
		double value = std::fabs(mat[idx(row, col, N)]);
		if (value > largest) {
		    largest = value;
		    p = row;
		    q = col;
		}
	    }
	}
	if (N == 1 || largest <= tolerance) {
	    converged = true;
	    break;
	}

	double app = mat[idx(p, p, N)];
	double aqq = mat[idx(q, q, N)];
	double apq = mat[idx(p, q, N)];
	double angle = 0.5 * std::atan2(2.0 * apq, aqq - app);
	double c = std::cos(angle);
	double s = std::sin(angle);

	for (int k = 0; k < N; ++k) {
	    if (k != p && k != q) {
		double akp = mat[idx(k, p, N)];
		double akq = mat[idx(k, q, N)];
		double new_kp = c * akp - s * akq;
		double new_kq = s * akp + c * akq;
		mat[idx(k, p, N)] = mat[idx(p, k, N)] = new_kp;
		mat[idx(k, q, N)] = mat[idx(q, k, N)] = new_kq;
	    }
	}
	mat[idx(p, p, N)] = c * c * app - 2.0 * s * c * apq + s * s * aqq;
	mat[idx(q, q, N)] = s * s * app + 2.0 * s * c * apq + c * c * aqq;
	mat[idx(p, q, N)] = mat[idx(q, p, N)] = 0.0;

	if (vectors) {
	    for (int row = 0; row < N; ++row) {
		double vip = vec[idx(row, p, N)];
		double viq = vec[idx(row, q, N)];
		vec[idx(row, p, N)] = c * vip - s * viq;
		vec[idx(row, q, N)] = s * vip + c * viq;
	    }
	}
    }

    if (!converged) {
	*info = 1;
	return;
    }

    std::vector<int> order(N);
    for (int i = 0; i < N; ++i) {
	order[i] = i;
    }
    std::sort(order.begin(), order.end(), [&](int left, int right) {
	return mat[idx(left, left, N)] < mat[idx(right, right, N)];
    });

    std::vector<double> sorted_vec(N * N);
    for (int col = 0; col < N; ++col) {
	int source_col = order[col];
	w[col] = mat[idx(source_col, source_col, N)];
	if (vectors) {
	    for (int row = 0; row < N; ++row) {
		sorted_vec[idx(row, col, N)] = vec[idx(row, source_col, N)];
	    }
	}
    }
    if (vectors) {
	for (int col = 0; col < N; ++col) {
	    for (int row = 0; row < N; ++row) {
		a[idx(row, col, *lda)] = sorted_vec[idx(row, col, N)];
	    }
	}
    }
    *info = 0;
}

void F77_FUNC(dgesv, DGESV)(const int *n, const int *nrhs, double *a,
			    const int *lda, int *ipiv, double *b,
			    const int *ldb, int *info)
{
    int N = *n;
    for (int k = 0; k < N; ++k) {
	int pivot = k;
	double pivot_abs = std::fabs(a[idx(k, k, *lda)]);
	for (int row = k + 1; row < N; ++row) {
	    double value = std::fabs(a[idx(row, k, *lda)]);
	    if (value > pivot_abs) {
		pivot_abs = value;
		pivot = row;
	    }
	}
	if (pivot_abs == 0.0) {
	    *info = k + 1;
	    return;
	}
	ipiv[k] = pivot + 1;
	if (pivot != k) {
	    for (int col = 0; col < N; ++col) {
		std::swap(a[idx(k, col, *lda)], a[idx(pivot, col, *lda)]);
	    }
	    for (int rhs = 0; rhs < *nrhs; ++rhs) {
		std::swap(b[idx(k, rhs, *ldb)], b[idx(pivot, rhs, *ldb)]);
	    }
	}
	for (int row = k + 1; row < N; ++row) {
	    a[idx(row, k, *lda)] /= a[idx(k, k, *lda)];
	    for (int col = k + 1; col < N; ++col) {
		a[idx(row, col, *lda)] -=
		    a[idx(row, k, *lda)] * a[idx(k, col, *lda)];
	    }
	}
    }

    for (int rhs = 0; rhs < *nrhs; ++rhs) {
	for (int row = 1; row < N; ++row) {
	    for (int col = 0; col < row; ++col) {
		b[idx(row, rhs, *ldb)] -=
		    a[idx(row, col, *lda)] * b[idx(col, rhs, *ldb)];
	    }
	}
	for (int row = N - 1; row >= 0; --row) {
	    for (int col = row + 1; col < N; ++col) {
		b[idx(row, rhs, *ldb)] -=
		    a[idx(row, col, *lda)] * b[idx(col, rhs, *ldb)];
	    }
	    b[idx(row, rhs, *ldb)] /= a[idx(row, row, *lda)];
	}
    }
    *info = 0;
}

void F77_FUNC(dsysv, DSYSV)(const char *, const int *n, const int *nrhs,
			    double *a, const int *lda, int *ipiv, double *b,
			    const int *ldb, double *work, const int *lwork,
			    int *info)
{
    if (*lwork == -1) {
	work[0] = std::max(1, *n);
	*info = 0;
	return;
    }
    F77_FUNC(dgesv, DGESV)(n, nrhs, a, lda, ipiv, b, ldb, info);
}

void F77_FUNC(dpotrf, DPOTRF)(const char *uplo, const int *n, double *a,
			      const int *lda, const int *info);

void F77_FUNC(dposv, DPOSV)(const char *uplo, const int *n, const int *nrhs,
			    double *a, const int *lda, double *b,
			    const int *ldb, int *info)
{
    F77_FUNC(dpotrf, DPOTRF)(uplo, n, a, lda, info);
    if (*info != 0) {
	return;
    }
    bool upper = *uplo == 'U' || *uplo == 'u';
    int N = *n;
    for (int rhs = 0; rhs < *nrhs; ++rhs) {
	if (upper) {
	    for (int row = 0; row < N; ++row) {
		for (int col = 0; col < row; ++col) {
		    b[idx(row, rhs, *ldb)] -=
			a[idx(col, row, *lda)] * b[idx(col, rhs, *ldb)];
		}
		b[idx(row, rhs, *ldb)] /= a[idx(row, row, *lda)];
	    }
	    for (int row = N - 1; row >= 0; --row) {
		for (int col = row + 1; col < N; ++col) {
		    b[idx(row, rhs, *ldb)] -=
			a[idx(row, col, *lda)] * b[idx(col, rhs, *ldb)];
		}
		b[idx(row, rhs, *ldb)] /= a[idx(row, row, *lda)];
	    }
	}
	else {
	    for (int row = 0; row < N; ++row) {
		for (int col = 0; col < row; ++col) {
		    b[idx(row, rhs, *ldb)] -=
			a[idx(row, col, *lda)] * b[idx(col, rhs, *ldb)];
		}
		b[idx(row, rhs, *ldb)] /= a[idx(row, row, *lda)];
	    }
	    for (int row = N - 1; row >= 0; --row) {
		for (int col = row + 1; col < N; ++col) {
		    b[idx(row, rhs, *ldb)] -=
			a[idx(col, row, *lda)] * b[idx(col, rhs, *ldb)];
		}
		b[idx(row, rhs, *ldb)] /= a[idx(row, row, *lda)];
	    }
	}
    }
    *info = 0;
}

void F77_FUNC(dpotrf, DPOTRF)(const char *uplo, const int *n, double *a,
			      const int *lda, const int *info)
{
    bool upper = *uplo == 'U' || *uplo == 'u';
    int N = *n;
    if (upper) {
	std::vector<double> lower(N * N);
	for (int col = 0; col < N; ++col) {
	    for (int row = 0; row < N; ++row) {
		lower[idx(row, col, N)] = row >= col ?
		    a[idx(col, row, *lda)] : a[idx(row, col, *lda)];
	    }
	}
	if (!cholesky_lower(&lower[0], N, N)) {
	    set_info(info, 1);
	    return;
	}
	for (int col = 0; col < N; ++col) {
	    for (int row = 0; row < N; ++row) {
		a[idx(row, col, *lda)] = row <= col ?
		    lower[idx(col, row, N)] : 0.0;
	    }
	}
    }
    else if (!cholesky_lower(a, N, *lda)) {
	set_info(info, 1);
	return;
    }
    set_info(info, 0);
}

void F77_FUNC(dpotri, DPOTRI)(const char *uplo, const int *n, double *a,
			      const int *lda, const int *info)
{
    bool upper = *uplo == 'U' || *uplo == 'u';
    int N = *n;
    std::vector<double> inv_tri(N * N, 0.0);
    for (int col = 0; col < N; ++col) {
	for (int row = 0; row < N; ++row) {
	    inv_tri[idx(row, col, N)] = a[idx(row, col, *lda)];
	}
    }
    invert_triangular(uplo, "N", n, &inv_tri[0], &N, info);
    if (*info != 0) {
	return;
    }

    std::vector<double> inv(N * N, 0.0);
    for (int col = 0; col < N; ++col) {
	for (int row = 0; row < N; ++row) {
	    double sum = 0.0;
	    for (int k = 0; k < N; ++k) {
		if (upper) {
		    sum += inv_tri[idx(row, k, N)] * inv_tri[idx(col, k, N)];
		}
		else {
		    sum += inv_tri[idx(k, row, N)] * inv_tri[idx(k, col, N)];
		}
	    }
	    inv[idx(row, col, N)] = sum;
	}
    }
    for (int col = 0; col < N; ++col) {
	for (int row = 0; row < N; ++row) {
	    a[idx(row, col, *lda)] = inv[idx(row, col, N)];
	}
    }
    set_info(info, 0);
}

void F77_FUNC(dtrtri, DTRTRI)(const char *uplo, const char *diag,
			      const int *n, double *a, const int *lda,
			      const int *info)
{
    invert_triangular(uplo, diag, n, a, lda, info);
}

} // extern "C"
