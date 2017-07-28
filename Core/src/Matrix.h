#ifndef __MATRIX_H__
#define __MATRIX_H__


#include <stdio.h>
#include <stdlib.h>
#include "EasyBMP.h"

class Pixel
{
public:
    double r;
    double g;
    double b;

public:
    static Pixel Zero;

public:
    Pixel(){ r=g=b=0;}
    Pixel(double r, double g, double b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    ebmpBYTE r255() {return round(r*255);}
    ebmpBYTE g255() {return round(g*255);}
    ebmpBYTE b255() {return round(b*255);}

    void log()
    {
        printf("%f,%f,%f ", b, g, r);
    }

    friend Pixel operator - (const Pixel& a, const Pixel& b)
    {
        return Pixel(a.r - b.r, a.g - b.g, a.b - b.b);
    }

    friend Pixel operator * (const Pixel& a, double b)
    {
        return Pixel(a.r * b, a.g * b, a.b * b);
    }

    static Pixel distance (const Pixel& a, const Pixel& b )
    {
        return Pixel( (a.r-b.r)*(a.r-b.r),
                      (a.g-b.g)*(a.g-b.g),
                      (a.b-b.b)*(a.b-b.b));
    }

    Pixel& operator = (double v)
    {
        r = g = b = v;
        return *this;
    }

    Pixel&operator += (double v)
    {
        r += v;
        g += v;
        b += v;

        return *this;
    }
    Pixel& operator += (const Pixel& other)
    {
        r+=other.r;
        g+=other.g;
        b+=other.b;

        return *this;
    }
    
    Pixel& operator -= (const Pixel& other)
    {
        r-=other.r;
        g-=other.g;
        b-=other.b;

        return *this;
    }
    Pixel& operator *= (const Pixel& other)
    {
        r*=other.r;
        g*=other.g;
        b*=other.b;

        return *this;
    }
    Pixel& operator *= (double v)
    {
        r*=v;
        g*=v;
        b*=v;

        return *this;
    }
    
    Pixel& operator /= (const Pixel& other)
    {
        r/=other.r;
        g/=other.g;
        b/=other.b;

        return *this;
    }
};

class DataBase;

struct Matrix
{
    friend class DataBase;
private:
    int m_h;
    int m_w;
    bool m_isGray;
    Pixel *p;
    
public:
    Matrix(BMP& bmp) 
    {
        p = NULL;
        init(bmp.TellHeight(), bmp.TellWidth(), bmp.TellBitDepth()==8);

        for(int h = 0; h < m_h; h++ )
        {
          for( int w = 0; w < m_w ; w++ )
          {
            RGBApixel rgb = bmp.GetPixel(w, h);
            Pixel pixel( double(rgb.Red)/255.0, 
                        double(rgb.Green)/255.0,
                        double(rgb.Blue)/255.0);
            set(h, w, pixel);
          }
        }
    }
    Matrix(const Matrix& other)
    {
        p = NULL;
        init(other.m_h, other.m_w, other.m_isGray);

        memcpy(p, other.p, sizeof(Pixel)*m_h*m_w);
//        for (int i = 0; i < m_h*m_w; i++)
//        {
//            p[i] = other.p[i];
//        }
    }
    Matrix& operator = (const Matrix& ref)
    {
        if (this == &ref)
        {
            return *this;
        }
        
        init(ref.m_h, ref.m_w, ref.m_isGray);


        for (int i = 0; i < m_h*m_w; i++)
        {
            p[i] = ref.p[i];
        }

        
        return *this;
    }

    Matrix& operator += (const Matrix& v)
    {
        for (int pos = 0; pos < m_h*m_w; pos++)
        {
            p[pos] += v.p[pos];
        }

        return *this;
    }
    Matrix& operator += (double eps)
    {
        for (int pos = 0; pos < m_h*m_w; pos++)
        {
            p[pos] += eps;
        }
        return *this;
    }

    Matrix& operator *= (const Matrix& v)
    {
        for (int pos = 0; pos < m_h*m_w; pos++)
        {
            p[pos] *= v.p[pos];
        }

        return *this;
    }
    Matrix& operator *= (double v)
    {
        for (int pos = 0; pos < m_h*m_w; pos++)
        {
            p[pos] *= v;
        }

        return *this;
    }
    
    Matrix& operator /= (const Matrix& v)
    {
    #pragma omp parallel for
        for (int pos = 0; pos < m_h*m_w; pos++)
        {
            p[pos] /= v.p[pos];
        }

        return *this;
    }
    Matrix& operator -= (const Matrix& v)
    {
        for (int pos = 0; pos < m_h*m_w; pos++)
        {
            p[pos] -= v.p[pos];
        }

        return *this;
    }

    friend Matrix operator + (const Matrix& a, const Matrix& b)
    {
        return Matrix(a) += b;
    }
    friend Matrix operator + (const Matrix& a, double eps)
    {
        Matrix r(a);
       return r += eps;
    }
    friend Matrix operator - (const Matrix& a, const Matrix& b)
    {
        Matrix r(a);
        return r -= b;
    }
    friend Matrix operator * (const Matrix& a, const Matrix& b)
    {
        Matrix r(a);
         return r *= b;
    }
    friend Matrix operator * (const Matrix& a, double eps)
    {
       Matrix r(a);
       return r *= eps;
    }
    
    friend Matrix operator / (const Matrix& a, const Matrix& b)
    {
        return Matrix(a) /= b;
    }
    
    Matrix(int h, int w, bool isGray)
    {
        init(h, w, isGray);
    }
    ~Matrix()
    {
        if (p) free(p);
    }

    bool toBMP(BMP& bmp) const
    {
        bmp.SetBitDepth(24);
        bmp.SetSize(m_w, m_h);

        for (int w = 0; w < m_w; w++)
        {
            for (int h = 0; h < m_h; h++)
            {
                Pixel p = get(h, w);
            
                RGBApixel temp;
                temp.Red = p.r255();
                temp.Green = p.g255();
                temp.Blue = p.b255();
                temp.Alpha = 0;
                    
                bmp.SetPixel(w, h, temp);
            }
        }


        return true;
    }

    void show(const char* p=NULL ) const
    {
        return ;
        printf("%s = [\n", p);
    
        for(int i=0; i < m_h; i++ )
        {
          for( int j=0; j < m_w ; j++ )
          {
              Pixel p = get(i, j);
              p.log();
          }
          printf("; -------------\n");
        }
        printf("]\n\n\n");
    }

    void newsize(int h, int w)
    {
        if (p) free(p);
        
        p = NULL;
        init(h, w, m_isGray);
    }

    int Height() const {return m_h;} 
    int Width() const {return m_w;}

    void cum_for_every_h()
    {    
        //每行积分上一行的
        for (int i = 1; i < m_h; i++)
        {
            for (int j = 0; j < m_w; j++)
            {
                get(i,j) += get(i-1, j);
            }
        }
    }
    void cum_for_every_w()
    {    
        //每行积分上一行的
        for (int i = 1; i < m_w; i++)
        {
            for (int j = 0; j < m_h; j++)
            {
                get(j,i) += get(j, i-1);
            }
        }
    }

    void set_all_value_1()
    {
        for (int pos = 0; pos < m_h*m_w; pos++)
        {
            Pixel& t = p[pos];
            t.r = t.g = t.b = 1;
        }
    }

    void cum_diff_r_for_every_h(const Matrix& m, int r)
    {
        for (int i = 0; i < m_h; i++)
        {
            int min = i - r - 1;
            int max = i + r;
            if (max >= m_h)
            {
                max = m_h - 1;
            }
        
            for (int j = 0; j < m_w; j++)
            {
                get(i, j) = m.get(max, j) - ((min>=0)?m.get(min, j):Pixel::Zero);
            }
        }
    }

    void cum_diff_r_for_every_w(const Matrix& m, int r)
    {
        for (int i = 0; i < m_w; i++)
        {
            int min = i - r - 1;
            int max = i + r;
            if (max >= m_w)
            {
                max = m_w - 1;
            }
        
            for (int j = 0; j < m_h; j++)
            {
                get(j, i) = m.get(j, max) - ((min>=0)?m.get(j, min):Pixel::Zero);
            }
        }
    }

    void sum(int r2, const DataBase& db);

    void f2(const Matrix& m, int r);

    Pixel distance(int h1, int w1, int h2, int w2, int r) const
    {
        Pixel sum;
        for (int i = -r; i <= r; i++)
        {
            for (int j = -r; j <=r ; j++)
            {
                const Pixel& a = get(h1 + i, w1 + j);
                const Pixel& b = get(h2 + i, w2 + j);
                sum += Pixel::distance(a, b);
            }
        }
        return sum;
    }
    
protected:
    const Pixel& get(int i , int j) const
    {
        return p[i*m_w+j];
    }

    Pixel& get(int i , int j) 
    {
        return p[i*m_w+j];
    }

    void set(int h, int w, Pixel v)
    {
        p[ h * m_w + w ] = v;
    }



private:
    Matrix();

    
    void init(int h, int w, bool isGray)
    {
        m_h = h;
        m_w = w;
        m_isGray = isGray;

        if (p)
        {
            free(p);
        }
        p = (Pixel*)malloc(m_h*m_w*sizeof(Pixel));
    }
};

#endif /* __MATRIX_H__ */

