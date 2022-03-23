#include <fftw3.h> 
int main( int argc, char *argv[]) 
{ 
    fftw_complex *inx,*outx; 
    fftw_plan ftpx; 
    long n,i; 
    double xreal,ximag;
    FILE *fpin,*fpout; 
    printf("reading\n"); 
    fpin=fopen("input.txt","r"); 
    fscanf(fpin,"%ld",&n); 
    printf("There are %ld data\n",n); 
    printf("initializing 1D FFT...\n"); 
    inx = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n); 
    outx= (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n); 
    ftpx = fftw_plan_dft_1d(n, inx, outx, FFTW_FORWARD, FFTW_MEASURE); 
    printf("FFT initialized\n Reading data\n"); 
    for(i=0;i<n;i++) 
    { 
        printf("%ld ",i); 
        fscanf(fpin,"%lg %lg",&xreal,&ximag); 
        printf("%lg %lg\n",xreal,ximag); 
        inx[i][0]=xreal; 
        inx[i][1]=ximag; 
    } 
    printf("Reading completed\n"); 
    fftw_execute(ftpx); 
    printf("Output\n"); 
    fpout=fopen("out.txt","w"); 
    for(i=0;i<n;i++) 
    { 
        fprintf(fpout,"%ld\t%lg\t%lg\n",i,outx[i][0],outx[i][1]); 
    } 
    printf("Results saved in out.txt successfully\n"); 
    fftw_destroy_plan(ftpx); 
    fftw_free(inx); 
    fftw_free(outx); 
}