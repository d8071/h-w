#include <stdio.h>

double scalarProduct(int n,double x1[n],double x2[n]) {
    int i;
    double res = 0.0;
    for (i=0;i<n;i++)
        res += x1[i]*x2[i];
    return res;
}

void GS_orth(int n,int k,double mat[k][n],double orth_mat[k][n]) {
    int i,j,h;
    double tmp1,tmp2;
    for (i=0;i<k;i++)
        for (j=0;j<n;j++)
            orth_mat[i][j] = mat[i][j];
    for (i=1;i<k;i++) {
        for (j=0;j<i;j++) {
            tmp1 = scalarProduct(n,mat[i],orth_mat[j]);
            tmp2 = scalarProduct(n,orth_mat[j],orth_mat[j]);
            printf("\n ! %d %d %lf %lf %lf\n",i,j,tmp1,tmp2,tmp1/tmp2);
            for (h=0;h<n;h++) {
                orth_mat[i][h] -= (tmp1/tmp2 * orth_mat[j][h]);
            }
        }
    }
    return;
}

int main() {
    int n,k;

    printf("Space dimension:\n");
    scanf("%d",&n);

    printf("Number of vectors:\n");
    scanf("%d",&k);

    double mat[k][n];
    int i,j,z,n1 = n;

    printf("Vectors:\n");
    for (i = 0; i<k; i++) {
        z=0;
        for (j = 0; j<n; j++) {
            scanf("%lf",&mat[i][j]);
            if (mat[i][j] == 0.0) z++;
        }
        if (z == n) {i--; k--; n1--;}
    }

    double orth_mat[k][n];

    GS_orth(n,k,mat,orth_mat);

    for (i=0;i<k;i++) {
        for (j=0;j<n;j++)
            printf("%.15lf ",orth_mat[i][j]);
        printf("\n");
    }

    printf("\n");

    for (i=0;i<k-1;i++) {
        printf("%.15lf\n",scalarProduct(n,orth_mat[i],orth_mat[i+1]));
    }

    return 0;
}


