#include "Matrix.h"
#include "DataBase.h"
#include "Log.h"

Pixel Pixel::Zero = Pixel(0,0,0);

void Matrix::sum(int r2, const DataBase& db)
{
    for (int i = r2; i < m_h-r2; i++)
    {
        for (int j = r2; j< m_w-r2; j++)
        {
            get(i,j) = db.getSum(i,j);
        }
    }
}

void Matrix::f2(const Matrix &m, int r)
{
    for (int h = 0; h < m_h; h++)
    {
        for (int w= 0; w < m_w; w++)
        {
            Pixel sum;
            for (int i = h-r; i <= h+r; i++)
            {
                for (int j = w-r; j <= w+r; j++)
                {
                    if (i < 0 || j < 0 || i >= m_h || j >= m_w)
                    {
                        continue;
                    }

                    int diffH = abs(i - h);
                    int diffW = abs(j - w);

                    int diff = (diffH > diffW) ? diffH : diffW;
                    int dist = r - diff;

                    sum += m.get(i, j) * dist;
                }
            }

            get(h, w) = sum;
        }
    }
}