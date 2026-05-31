#include <math.h>
#include <stdio.h>

extern void dpotrf_(const char *uplo, const int *n, double *a,
                    const int *lda, int *info);
extern void dpotri_(const char *uplo, const int *n, double *a,
                    const int *lda, int *info);
extern void dsyev_(const char *jobz, const char *uplo, const int *n, double *a,
                   const int *lda, double *w, double *work, const int *lwork,
                   int *info);
extern void dgesv_(const int *n, const int *nrhs, double *a, const int *lda,
                   int *ipiv, double *b, const int *ldb, int *info);

static int require_ok(int info, const char *name)
{
    if (info != 0) {
        printf("%s info=%d\n", name, info);
        return 1;
    }
    return 0;
}

int main(void)
{
    int n = 2;
    int lda = 2;
    int info = 0;
    char lower = 'L';

    double chol[4] = {4.0, 1.0, 1.0, 3.0};
    printf("calling dpotrf\n");
    fflush(stdout);
    dpotrf_(&lower, &n, chol, &lda, &info);
    if (require_ok(info, "dpotrf")) return 1;

    printf("calling dpotri\n");
    fflush(stdout);
    dpotri_(&lower, &n, chol, &lda, &info);
    if (require_ok(info, "dpotri")) return 1;

    double eig[4] = {4.0, 1.0, 1.0, 3.0};
    double values[2] = {0.0, 0.0};
    int lwork_query = -1;
    double work_query = 0.0;
    char values_only = 'N';
    char upper = 'U';
    printf("calling dsyev query\n");
    fflush(stdout);
    dsyev_(&values_only, &upper, &n, eig, &lda, values, &work_query,
           &lwork_query, &info);
    if (require_ok(info, "dsyev query")) return 1;
    int lwork = (int)ceil(work_query);
    double work[64] = {0.0};
    if (lwork > 64) lwork = 64;
    printf("calling dsyev\n");
    fflush(stdout);
    dsyev_(&values_only, &upper, &n, eig, &lda, values, work, &lwork, &info);
    if (require_ok(info, "dsyev")) return 1;

    double solve_a[4] = {4.0, 1.0, 1.0, 3.0};
    double solve_b[2] = {1.0, 2.0};
    int ipiv[2] = {0, 0};
    int nrhs = 1;
    printf("calling dgesv\n");
    fflush(stdout);
    dgesv_(&n, &nrhs, solve_a, &lda, ipiv, solve_b, &n, &info);
    if (require_ok(info, "dgesv")) return 1;

    printf("ok %.6f %.6f %.6f %.6f\n", chol[0], values[0], values[1], solve_b[0]);
    return 0;
}
