#include <stdio.h>
#include <string.h>
#include <math.h>
#define PI 3.1415926535

int n, dc, dg, ld;
char w[8];
char w1[8] = "Rain", w2[8] = "Sun";
char w3[8] = "Cloud", w4[8] = "Fog", w5[8] = "Wind";
double nbg, nd;
int nbc, bc, bg, tld;

int amicable(int n, int ld);
int case_wind(int n, int dc, int dg, int ld, char w[8]);
int case_rain(int n, int dc, int dg, int ld, char w[8]);
void case_fog(int n, int dc, int dg, int ld, char w[8]);
int case_cloud(int n, int dc, int dg, int ld, char w[8]);
int case_sun(int n, int dc, int dg, int ld, char w[8]);

void main()
{
    FILE *f;
    f = fopen("input.inp", "r");
    fscanf(f, "%d %d %d %d %s", &n, &dc, &dg, &ld, &w);
    fclose(f);

    if (n > 1000 || ld < 1 || ld > 300)
    {
        bc = -1;
        bg = -1;
    }

    else if (strcmp(w, w1) != 0 && strcmp(w, w2) != 0 && strcmp(w, w3) != 0 && strcmp(w, w4) != 0 && strcmp(w, w5) != 0)
    {
        bc = -1;
        bg = -1;
    }

    else
    {
        if (strcmp(w, w5) == 0)
        {
            case_wind(n, dc, dg, ld, w);
        }

        else if (strcmp(w, w1) == 0)
        {
            case_rain(n, dc, dg, ld, w);
        }

        else if (strcmp(w, w2) == 0)
        {
            case_sun(n, dc, dg, ld, w);
        }

        else if (strcmp(w, w4) == 0)
        {
            case_fog(n, dc, dg, ld, w);
        }

        else // w3
        {
            case_cloud(n, dc, dg, ld, w);
        }
    }

    FILE *fw;
    fw = fopen("output.out", "w");
    if ((bc + bg) < 0)
    {
        fprintf(fw, "-1 -1 %d", n);
    }
    else
    {
        fprintf(fw, "%d %d %.3lf", bc, bg, nd);
    }

    fclose(fw);
}

int amicable(int n, int ld)
{
    int s1 = 0;
    int s2 = 0;
    int j;

    for (j = 1; j <= n / 2; j++)
    {
        if (n % j == 0)
            s1 = s1 + j;
    }

    for (j = 1; j <= ld / 2; j++)
    {
        if (ld % j == 0)
            s2 = s2 + j;
    }

    if (s1 == ld && s2 == n)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int case_wind(int n, int dc, int dg, int ld, char w[8])
{
    nbc = dc * dc;
    nbg = (dg * dg * PI) / 4;
    bc = n / nbc;
    nd = n - bc * nbc;
    bg = nd / nbg;
    nd = nd - bg * nbg;
    int max;
    max = bc;

    // ld vs (bc + bg)
    tld = bc + bg;

    if (tld > ld)
    {
        if (bc > ld)
        {
            bc = ld;
            bg = 0;
            nd = n - bc * nbc;
        }
        else
        {
            bc = max;
            bg = ld - bc;
            nd = n - bc * nbc - bg * nbg;
        }
    }
    else
    {
        bc = bc;
        bg = bg;
        nd = nd;
    }

    return bc, bg, nd;
}

int case_rain(int n, int dc, int dg, int ld, char w[8])
{
    int temp, bct, bgt;
    float ndbc, ndbg;
    nbc = dc * dc;
    nbg = (dg * dg * PI) / 4;
    nd = n;

    if (n >= 0)
    {
        bc = nd / nbc;
        nd = (float)nd - bc * nbc;
        bg = nd / nbg;
        nd = (float)nd - bg * nbg;
    }

    temp = bc + bg;
    if (temp > ld)
    {
        temp = ld;
    }
    else
    {
        temp = temp;
    }

    if (temp % 2 == 0)
    {
        temp = temp / 2;
    }
    else
    {
        temp = (temp + 1) / 1.5;
    }

    bc = temp;
    bg = temp;
    nd = n - bc * nbc - bg * nbg;

    bct = nd / nbc;
    bgt = nd / nbg;

    ndbc = nd - (bc + bct) * nbc - bg * nbg;
    ndbg = nd - (bg + bgt) * nbg - bc * nbc;

    if (ndbc < ndbg)
    {
        bc = bc + bct;
    }
    else
    {
        bg = bg + bgt;
    }
    nd = n - bc * nbc - bg * nbg;

    while (nd < 0)
    {
        bc = bc - 1;
        bg = bg - 1;
        nd = n - bc * nbc - bg * nbg;
    }

    return bc, bg, nd;
}

void case_fog(int n, int dc, int dg, int ld, char w[8])
{
    bc = dc;
    bg = dg;
    nd = n;
}

int case_cloud(int n, int dc, int dg, int ld, char w[8])
{
    if (amicable(n, ld) == 1)
    {
        bc = 0;
        bg = 0;
        nd = n;
    }
    else
    {
        nbc = dc * dc;
        nbg = (dg * dg * PI) / 4;
        bg = n / nbg;
        nd = n - bg * nbg;
        bc = nd / nbc;
        nd = nd - bc * nbc;
        int max;
        max = bg;

        // ld vs (bc + bg)
        tld = bc + bg;

        if (tld > ld)
        {
            if (bg > ld)
            {
                bg = ld;
                bc = 0;
                nd = n - bg * nbg;
            }
            else
            {
                bg = max;
                bc = ld - bg;
                nd = n - bc * nbc - bg * nbg;
            }
        }
        else
        {
            bc = bc;
            bg = bg;
            nd = nd;
        }

        return bc, bg, nd;
    }
}

int case_sun(int n, int dc, int dg, int ld, char w[8])
{
    int g, h, ws, ldm;
    float nt;
    g = dc % 6;
    h = ld % 5;

    // g=0 h=[0:4]
    if (g == 0 && h == 0)
    {
        nt = n + ((n * 5) / 100);
        ldm = ld - 5;
    }
    else if (g == 0 && h == 1)
    {
        nt = n + ((n * 20) / 100);
        ldm = ld - 20;
    }
    else if (g == 0 && h == 2)
    {
        nt = n + ((n * 15) / 100);
        ldm = ld - 15;
    }
    else if (g == 0 && h == 3)
    {
        nt = n + ((n * 12) / 100);
        ldm = ld - 12;
    }
    else if (g == 0 && h == 4)
    {
        nt = n + ((n * 10) / 100);
        ldm = ld - 10;
    }
    // g=1 h=[0:4]
    else if (g == 1 && h == 0)
    {
        nt = n + ((n * 7) / 100);
        ldm = ld - 7;
    }
    else if (g == 1 && h == 1)
    {
        nt = n + ((n * 5) / 100);
        ldm = ld - 5;
    }
    else if (g == 1 && h == 2)
    {
        nt = n + ((n * 20) / 100);
        ldm = ld - 20;
    }
    else if (g == 1 && h == 3)
    {
        nt = n + ((n * 15) / 100);
        ldm = ld - 15;
    }
    else if (g == 1 && h == 4)
    {
        nt = n + ((n * 12) / 100);
        ldm = ld - 12;
    }
    // g=2 h=[0:4]
    else if (g == 2 && h == 0)
    {
        nt = n + ((n * 10) / 100);
        ldm = ld - 10;
    }
    else if (g == 2 && h == 1)
    {
        nt = n + ((n * 7) / 100);
        ldm = ld - 7;
    }
    else if (g == 2 && h == 2)
    {
        nt = n + ((n * 5) / 100);
        ldm = ld - 5;
    }
    else if (g == 2 && h == 3)
    {
        nt = n + ((n * 20) / 100);
        ldm = ld - 20;
    }
    else if (g == 2 && h == 4)
    {
        nt = n + ((n * 15) / 100);
        ldm = ld - 15;
    }
    // g=3 h=[0:4]
    else if (g == 3 && h == 0)
    {
        nt = n + ((n * 12) / 100);
        ldm = ld - 12;
    }
    else if (g == 3 && h == 1)
    {
        nt = n + ((n * 10) / 100);
        ldm = ld - 10;
    }
    else if (g == 3 && h == 2)
    {
        nt = n + ((n * 7) / 100);
        ldm = ld - 7;
    }
    else if (g == 3 && h == 3)
    {
        nt = n + ((n * 5) / 100);
        ldm = ld - 5;
    }
    else if (g == 3 && h == 4)
    {
        nt = n + ((n * 20) / 100);
        ldm = ld - 20;
    }
    // g=4 h=[0:4]
    else if (g == 4 && h == 0)
    {
        nt = n + ((n * 15) / 100);
        ldm = ld - 15;
    }
    else if (g == 4 && h == 1)
    {
        nt = n + ((n * 12) / 100);
        ldm = ld - 12;
    }
    else if (g == 4 && h == 2)
    {
        nt = n + ((n * 10) / 100);
        ldm = ld - 10;
    }
    else if (g == 4 && h == 3)
    {
        nt = n + ((n * 7) / 100);
        ldm = ld - 7;
    }
    else if (g == 4 && h == 4)
    {
        nt = n + ((n * 5) / 100);
        ldm = ld - 5;
    }
    // g=5 h=[0:4]
    else if (g == 5 && h == 0)
    {
        nt = n + ((n * 20) / 100);
        ldm = ld - 20;
    }
    else if (g == 5 && h == 1)
    {
        nt = n + ((n * 15) / 100);
        ldm = ld - 15;
    }
    else if (g == 5 && h == 2)
    {
        nt = n + ((n * 12) / 100);
        ldm = ld - 12;
    }
    else if (g == 5 && h == 3)
    {
        nt = n + ((n * 10) / 100);
        ldm = ld - 10;
    }
    else
    {
        nt = n + ((n * 7) / 100);
        ldm = ld - 7;
    }

    ws = (dc + dg) % 3;

    if (ws == 0) // rain
    {
        int temp, bct, bgt;
        float ndbc, ndbg;
        nbc = dc * dc;
        nbg = (dg * dg * PI) / 4;
        nd = nt;

        if (nt >= 0)
        {
            bc = nd / nbc;
            nd = (float)nd - bc * nbc;
            bg = nd / nbg;
            nd = (float)nd - bg * nbg;
        }

        temp = bc + bg;
        if (temp > ldm)
        {
            temp = ldm;
        }
        else
        {
            temp = temp;
        }

        temp = bc + bg;
        if (temp % 2 == 0)
        {
            temp = temp / 2;
        }
        else
        {
            temp = (temp + 1) / 1.5;
        }

        bc = temp;
        bg = temp;
        nd = nt - bc * nbc - bg * nbg;

        bct = nd / nbc;
        bgt = nd / nbg;

        ndbc = nd - (bc + bct) * nbc - bg * nbg;
        ndbg = nd - (bg + bgt) * nbg - bc * nbc;

        if (ndbc < ndbg)
        {
            bc = bc + bct;
        }
        else
        {
            bg = bg + bgt;
        }
        nd = nt - bc * nbc - bg * nbg;

        while (nd < 0)
        {
            bc = bc - 1;
            bg = bg - 1;
            nd = nt - bc * nbc - bg * nbg;
        }

        return bc, bg, nd;
    }

    else if (ws == 1) // wind
    {
        nbc = dc * dc;
        nbg = (dg * dg * PI) / 4;
        bc = nt / nbc;
        nd = nt - bc * nbc;
        bg = nd / nbg;
        nd = nd - bg * nbg;
        int max;
        max = bc;

        // ld vs (bc + bg)
        tld = bc + bg;

        if (tld > ldm)
        {
            if (bc > ldm)
            {
                bc = ldm;
                bg = 0;
                nd = nt - bc * nbc;
            }
            else
            {
                bc = max;
                bg = ldm - bc;
                nd = nt - bc * nbc - bg * nbg;
            }
        }
        else
        {
            bc = bc;
            bg = bg;
            nd = nd;
        }

        return bc, bg, nd;
    }

    else if (ws == 2) // cloud
    {
        int s1 = 0;
        int s2 = 0;
        int j, banbe;

        for (j = 1; j <= nt / 2; j++)
        {
            if ((int)nt % j == 0)
                s1 = s1 + j;
        }

        for (j = 1; j <= ldm / 2; j++)
        {
            if (ldm % j == 0)
                s2 = s2 + j;
        }

        if (s1 == ldm && s2 == nt)
        {
            banbe = 1;
        }
        else
        {
            banbe = 0;
        }

        if (banbe == 1)
        {
            bc = 0;
            bg = 0;
            nd = nt;
        }

        else
        {
            nbc = dc * dc;
            nbg = (dg * dg * PI) / 4;
            bg = nt / nbg;
            nd = nt - bg * nbg;
            bc = nd / nbc;
            nd = nd - bc * nbc;
            int max;
            max = bg;

            // ld vs (bc + bg)
            tld = bc + bg;

            if (tld > ldm)
            {
                if (bg > ldm)
                {
                    bg = ldm;
                    bc = 0;
                    nd = nt - bg * nbg;
                }
                else
                {
                    bg = max;
                    bc = ldm - bg;
                    nd = nt - bc * nbc - bg * nbg;
                }
            }
            else
            {
                bc = bc;
                bg = bg;
                nd = nd;
            }

            return bc, bg, nd;
        }
    }
}