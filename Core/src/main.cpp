#include <time.h>
#include "EasyBMP.h"
#include "Matrix.h"
#include "DataBase.h"

Matrix box_filter_origin(const Matrix& imSrc, int r)
{	
	Matrix imCum = imSrc;
	imCum.cum_for_every_h();

	Matrix imDst = imCum;
	imDst.cum_diff_r_for_every_h(imCum, r);

	imCum = imDst;
	imCum.cum_for_every_w();

	imDst = imCum;
	imDst.cum_diff_r_for_every_w(imCum, r);

	return imDst;
}

Matrix box_filter2(const Matrix& imSrc, int r)
{
    Matrix im = imSrc;
    im.f2(imSrc, r);
    return im;
}

class NL_box_filter
{
public:
    NL_box_filter(int w, int r2, int N)
    {
        m_r2= r2;
        m_n = N;
        m_w = w;
    }

    Matrix operator() (const Matrix& imSrc, int r) const
    {
        (void)r;

        DataBase m_db(imSrc, m_n);
        m_db.index(m_w, m_r2);

        Matrix dst = imSrc;
        dst.sum(m_r2, m_db);

        return dst;
    }

private:
    int m_r2;
    int m_n;
    int m_w;
};

//.导向滤波彩色图模糊
template <class T>
Matrix guided_filter(const T& box_filter, const Matrix& I, const Matrix& p, int r, double eps)
{
	Matrix m1(p);
	m1.set_all_value_1();
	m1.show("m1");

	Matrix N = box_filter(m1, r);	
	N.show("N");

	//mean_I = boxfilter(I, r) ./ N;
	Matrix mean_I = box_filter(I, r) / N;  
	mean_I.show("mean_I");

	// mean_p = boxfilter(p, r) ./ N;
	Matrix mean_p = box_filter(p, r) / N;
	mean_p.show("mean_p");

	//mean_Ip = boxfilter(I.*p, r) ./ N;
	Matrix mean_Ip = box_filter(I*p, r) / N; 
	mean_Ip.show("mean_Ip");

	//cov_Ip = mean_Ip - mean_I .* mean_p; % this is the covariance of (I, p) in each local patch.
	Matrix cov_Ip = mean_Ip - mean_I * mean_p;
	cov_Ip.show("cov_Ip");
	
	//mean_II = boxfilter(I.*I, r) ./ N;
	Matrix mean_II = box_filter(I*I, r) / N;
	mean_II.show("mean_II");
	
	//var_I = mean_II - mean_I .* mean_I;
	Matrix var_I = mean_II - mean_I*mean_I;

	//a = cov_Ip ./ (var_I + eps); % Eqn. (5) in the paper;
	Matrix a = cov_Ip / (var_I + eps);
	a.show("a");
	
	//b = mean_p - a .* mean_I; % Eqn. (6) in the paper;
	Matrix b = mean_p - a * mean_I;
	b.show("b");

	//	mean_a = boxfilter(a, r) ./ N;
	Matrix mean_a = box_filter(a, r) / N;
	mean_a.show("mean_a");

	//mean_b = boxfilter(b, r) ./ N;
	Matrix mean_b = box_filter(b, r) / N;
	mean_b.show("mean_b");
	
	//q = mean_a .* I + mean_b; % Eqn. (8) in the paper;
	return mean_a * I + mean_b;

}

template<class T>
void run(const T& box_filter, const Matrix& guided, const Matrix& input, int r, double eps, const char* pszOutName)
{
    int begin = clock();
    Matrix output = guided_filter(box_filter, guided, input, r, eps);
    int end = clock();

    printf("begin = %d\n  end = %d\n elapsed_time = %d ms\n", begin,end,end-begin);
    output.show("output");
    BMP bmp_out;
    output.toBMP(bmp_out);

    bmp_out.WriteToFile(pszOutName);
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("a.exe x.bmp\n");
		return 1;
	}

	BMP bmp_input;
	if (!bmp_input.ReadFromFile(argv[1]))
	{
		printf("read %s failed\n", argv[1]);
		return 1;
	}

	printf("%d*%d bitdepth=%d numberofcoler=%d\n", 
		bmp_input.TellWidth(), bmp_input.TellHeight(), 
		bmp_input.TellBitDepth(), bmp_input.TellNumberOfColors());
	
	Matrix input(bmp_input);
	input.show("input");

	Matrix guided = input;
	guided.show("guided");

	int r = 4;
	double eps = 0.01;

    run(box_filter_origin, guided, input, r, eps, "out.bmp");
    run(box_filter2, guided,input,r,eps,"out2.bmp");


    if (0)
    {
        int N = 9;
        int r2 = 3;
        int w = 4;

        int begin = clock();
        NL_box_filter nl_box_filter(w, r2,N);
        Matrix output = guided_filter(nl_box_filter, guided, input, r, eps);
        int end = clock();

        printf("begin = %d\n   end=%d\n elapsed_time =  %d ms\n", begin, end, end - begin);
        output.show("output");

        BMP bmp_out;
        output.toBMP(bmp_out);

        bmp_out.WriteToFile("out.bmp");



    }
    return 0;
}


