#ifndef IMAGE_DATABASE_H
#define IMAGE_DATABASE_H

#include "Matrix.h"

struct Position
{
    Position()
    {
        value = 1000000;
        rh = rw = gh = gw = bh = bw = -1;
    }

    Pixel value;
    int rh; int rw;
    int gh; int gw;
    int bh; int bw;
};

class DataBase
{
public:
    DataBase(const Matrix& m, int n)
            :m_matrix(m)
    {
        m_h = m_matrix.Height();
        m_w = m_matrix.Width();
        m_n = n;

        printf("DataBase = %d\n", sizeof(Position)*m_h*m_w*m_n);
        m_data = new Position[m_h * m_w * m_n];
        printf("OK Database = %d\n", sizeof(Position)*m_h*m_w*m_n);
    }

    ~DataBase()
    {
        delete m_data;
    }

public:
    Pixel getSum(int i, int j) const
    {
        Pixel p;
        for (int k = 0; k < m_n; ++k) {
            const Position& pos = get(i,j,k);
            p.r += m_matrix.get(pos.rh, pos.rw).r;
            p.g += m_matrix.get(pos.gh, pos.gw).g;
            p.b += m_matrix.get(pos.bh, pos.bw).b;
        }
        return p;
    }

    void index(int w, int r2)
    {
        for (int i = r2; i < m_h-r2; i++)
        {
            for (int j = r2; j < m_w-r2; j++)
            {
                for (int m = -w; m <= w; m++)
                {
                    for (int n = -w; n <=w; n++)
                    {
                        int sx = i + m - r2;
                        int sy = j + n - r2;
                        int ex = i + m + r2;
                        int ey = i + n + r2;

                        if (sx >= 0 && sy >=0 && ex < m_h && ey < m_w)
                        {
                            Pixel d = m_matrix.distance(i, j, i+m, j+n, r2);
                            insert(i, j, d, i+m ,j+n);
                        }
                    }
                }
            }
        }
    }

private:
    const Position& get(int i, int j, int k) const
    {
        return m_data[i*m_w*m_n + j * m_n + k];
    }

    void insert(int i, int j, const Pixel& d, int newI, int newJ)
    {
        int maxPosR = 0;
        int maxPosG = 0;
        int maxPosB = 0;

        double maxValueR = -1;
        double maxValueG = -1;
        double maxValueB = -1;

        for (int n = i*m_w*m_n + j * m_n; n < i*m_w*m_n + j * m_n + m_n; n++)
        {
            if (m_data[n].value.r > maxValueR)
            {
                maxValueR = m_data[n].value.r;
                maxPosR = n;
            }
            if (m_data[n].value.g > maxValueG)
            {
                maxValueG = m_data[n].value.g;
                maxPosG = n;
            }
            if (m_data[n].value.b > maxValueB)
            {
                maxValueB = m_data[n].value.b;
                maxPosB = n;
            }
        }

        if (d.r < maxValueR)
        {
            m_data[maxPosR].value.r = d.r;
            m_data[maxPosR].rh = newI;
            m_data[maxPosR].rw = newJ;
        }
        if (d.g < maxValueG)
        {
            m_data[maxPosG].value.g = d.g;
            m_data[maxPosG].rh = newI;
            m_data[maxPosG].rw = newJ;
        }
        if (d.b < maxPosB)
        {
            m_data[maxPosB].value.b = d.b;
            m_data[maxPosB].rh = newI;
            m_data[maxPosB].rw = newJ;
        }

    }

private:
    const Matrix m_matrix;
    int m_h;
    int m_w;
    int m_n;
    Position* m_data;
};




#endif //IMAGE_DATABASE_H
