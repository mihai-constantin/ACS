===================== Results for auto-par version ====================
for P in 1 2                   ;\
    do OMP_NUM_THREADS=$P              ;\
       export OMP_NUM_THREADS           ;\
       SUNW_MP_THR_IDLE=spin            ;\
       export SUNW_MP_THR_IDLE          ;\
       SATS_LAB_HEADER=y                ;\
       export SATS_LAB_HEADER           ;\
   /bin/rm -f perf.dat              ;\
   for S in 5 10 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 150 200 250 300  325 350 375 400 500 525 550 575 600 650 675 700 725 750 800 900 950 975 1000 1025  1050 1100 1200 1300 1400 1500 1600 1700 1800 1900 1950 1975 2000 2025 2050 2100  3000 3500 4000 4500 5000 5500 6000                ;\
   do ./mxv_par.exe -m $S -n $S       ;\
      SATS_LAB_HEADER=n             ;\
   done                             ;\
   mv perf.dat par_$P"_procs.dat"  ;\
    done
----------------------------------------------------------------------
   M    N   Mem(KB)   Threads   Thresholds       Performance (Mflop/s)
                                 Row   Col       Row      Col      Lib
----------------------------------------------------------------------
   5    5      0.27         1      1     1     516.5    514.1    304.9
  10   10      0.94         1      1     1    1451.1   1620.1    752.1
  20   20      3.44         1      1     1    1987.0   2066.6   1266.7
  25   25      5.27         1      1     1    2760.4   2773.0   1423.2
  30   30      7.50         1      1     1    2176.9   2177.9   1446.4
  35   35     10.12         1      1     1    2709.8   2698.9    912.9
  40   40     13.12         1      1     1    3312.8   3110.6   1304.3
  45   45     16.52         1      1     1    2007.6   2689.4   1138.2
  50   50     20.31         1      1     1    2391.6   2551.6   1465.2
  55   55     24.49         1      1     1    2183.6   2273.7   1271.3
  60   60     29.06         1      1     1    2531.4   2626.5   1574.1
  65   65     34.02         1      1     1    2877.5   2988.5   1417.8
  70   70     39.38         1      1     1    2507.2   2578.8   1634.7
  75   75     45.12         1      1     1    2589.8   2615.2   1418.6
  80   80     51.25         1      1     1    2810.5   2820.9   1559.5
  85   85     57.77         1      1     1    2535.0   2593.4   1385.6
  90   90     64.69         1      1     1    2691.0   2686.2   1578.9
  95   95     71.99         1      1     1    2249.1   2291.5   1410.0
 100  100     79.69         1      1     1    2053.7   2077.0   1595.9
 150  150    178.12         1      1     1    1838.0   1837.1   1706.3
 200  200    315.62         1      1     1    1785.7   1865.8   1813.7
 250  250    492.19         1      1     1    2029.0   2004.1   1873.4
 300  300    707.81         1      1     1    2047.8   2011.9   1879.1
 325  325    830.27         1      1     1    1881.7   2030.1   1835.3
 350  350    962.50         1      1     1    2003.4   1999.5   1880.1
 375  375   1104.49         1      1     1    1317.2   1346.2   1119.4
 400  400   1256.25         1      1     1     755.5    781.5    784.4
 500  500   1960.94         1      1     1     720.5    735.2    787.6
 525  525   2161.52         1      1     1     689.8    698.6    767.2
 550  550   2371.88         1      1     1     707.3    679.2    644.5
 575  575   2591.99         1      1     1     717.6    652.6    769.5
 600  600   2821.88         1      1     1     734.6    733.0    763.0
 650  650   3310.94         1      1     1     711.1    716.1    774.2
 675  675   3570.12         1      1     1     633.9    707.6    757.1
 700  700   3839.06         1      1     1     708.2    716.4    768.6
 725  725   4117.77         1      1     1     674.3    710.8    773.5
 750  750   4406.25         1      1     1     715.1    720.6    772.4
 800  800   5012.50         1      1     1     726.0    698.8    779.8
 900  900   6342.19         1      1     1     707.9    704.2    564.3
 950  950   7065.62         1      1     1     714.4    711.5    782.3
 975  975   7441.99         1      1     1     455.3    682.0    717.0
1000 1000   7828.12         1      1     1     725.9    735.1    767.9
1025 1025   8224.02         1      1     1     692.8    462.1    554.3
1050 1050   8629.69         1      1     1     682.7    708.7    792.9
1100 1100   9470.31         1      1     1     683.0    711.8    778.4
1200 1200  11268.75         1      1     1     728.7    738.1    771.3
1300 1300  13223.44         1      1     1     711.9    718.2    741.1
1400 1400  15334.38         1      1     1     709.6    737.5    757.9
1500 1500  17601.56         1      1     1     711.4    700.6    748.2
1600 1600  20025.00         1      1     1     705.8    742.7    778.8
1700 1700  22604.69         1      1     1     718.3    725.0    786.4
1800 1800  25340.62         1      1     1     727.4    711.7    771.8
1900 1900  28232.81         1      1     1     696.4    608.9    706.5
1950 1950  29737.50         1      1     1     622.4    676.5    636.6
1975 1975  30504.49         1      1     1     759.2    706.9    713.4
2000 2000  31281.25         1      1     1     709.6    440.2    560.5
2025 2025  32067.77         1      1     1     654.1    709.3    782.9
2050 2050  32864.06         1      1     1     502.8    648.8    772.8
2100 2100  34485.94         1      1     1     719.4    730.6    776.8
3000 3000  70359.38         1      1     1     492.3    729.5    725.1
3500 3500  95757.81         1      1     1     712.0    708.4    777.1
4000 4000 125062.50         1      1     1     577.3    740.5    662.7
4500 4500 158273.44         1      1     1     658.5    689.5    717.0
5000 5000 195390.62         1      1     1     726.5    736.8    692.7
5500 5500 236414.06         1      1     1     656.2    615.0    642.6
6000 6000 281343.75         1      1     1     727.5    734.5    641.9
----------------------------------------------------------------------
   M    N   Mem(KB)   Threads   Thresholds       Performance (Mflop/s)
                                 Row   Col       Row      Col      Lib
----------------------------------------------------------------------
   5    5      0.27         2      1     1     516.3    512.0    302.6
  10   10      0.94         2      1     1    1454.9   1595.9    752.5
  20   20      3.44         2      1     1    1962.0   2092.7   1265.7
  25   25      5.27         2      1     1    2758.9   2777.2   1421.7
  30   30      7.50         2      1     1    2176.3   2177.4   1461.9
  35   35     10.12         2      1     1    2686.1   2716.2    937.8
  40   40     13.12         2      1     1    3312.9   3110.9   1278.3
  45   45     16.52         2      1     1    1081.3   2660.6   1125.9
  50   50     20.31         2      1     1    1395.5   1363.7   1450.2
  55   55     24.49         2      1     1    1605.0   1619.2   1249.9
  60   60     29.06         2      1     1    1498.9   1804.9   1568.1
  65   65     34.02         2      1     1    1993.3   2054.6   1410.3
  70   70     39.38         2      1     1    2019.2   2076.6   1607.9
  75   75     45.12         2      1     1    2506.1   2359.4   1648.0
  80   80     51.25         2      1     1    3003.0   2921.4   1862.5
  85   85     57.77         2      1     1    2885.8   2786.1   1869.1
  90   90     64.69         2      1     1    3040.0   3080.0   2050.8
  95   95     71.99         2      1     1    2947.9   2921.8   1935.8
 100  100     79.69         2      1     1    3363.6   3372.4   2187.8
 150  150    178.12         2      1     1    3225.8   3313.2   2295.4
 200  200    315.62         2      1     1    2963.5   3115.6   3148.1
 250  250    492.19         2      1     1    3492.6   2453.4   1976.6
 300  300    707.81         2      1     1    3024.4   3518.5   3298.8
 325  325    830.27         2      1     1    3106.0   2603.7   2333.1
 350  350    962.50         2      1     1    3641.7   2460.1   1888.6
 375  375   1104.49         2      1     1    3538.4   3139.3   2665.4
 400  400   1256.25         2      1     1    3280.7   2671.9   3099.3
 500  500   1960.94         2      1     1    2613.1   3122.0   3229.9
 525  525   2161.52         2      1     1    1650.5   1076.8   1559.9
 550  550   2371.88         2      1     1     420.9    478.1    479.2
 575  575   2591.99         2      1     1     775.9    396.7    691.1
 600  600   2821.88         2      1     1     776.9    773.0    753.0
 650  650   3310.94         2      1     1     728.5    767.1    875.2
 675  675   3570.12         2      1     1     842.5    511.7    828.1
 700  700   3839.06         2      1     1     892.0    723.3    977.2
 725  725   4117.77         2      1     1     448.0    486.8    386.8
 750  750   4406.25         2      1     1     467.9    553.1    900.1
 800  800   5012.50         2      1     1     404.2    388.3    514.8
 900  900   6342.19         2      1     1     470.9    374.4    684.0
 950  950   7065.62         2      1     1     652.4    540.1    712.3
 975  975   7441.99         2      1     1     268.8    496.8    489.6
1000 1000   7828.12         2      1     1     622.6    490.3   1042.6
1025 1025   8224.02         2      1     1     392.5    350.3    498.3
1050 1050   8629.69         2      1     1     330.2    219.9    523.1
1100 1100   9470.31         2      1     1     770.6    665.4    677.6
1200 1200  11268.75         2      1     1     656.2    526.8    668.3
1300 1300  13223.44         2      1     1     397.8    612.5    457.0
1400 1400  15334.38         2      1     1     802.9    821.8    851.7
1500 1500  17601.56         2      1     1     450.8    408.1    443.9
1600 1600  20025.00         2      1     1     386.9    519.9    546.7
1700 1700  22604.69         2      1     1     568.3    556.4    466.2
1800 1800  25340.62         2      1     1     601.6    665.5    589.9
1900 1900  28232.81         2      1     1     681.3    885.9    923.5
1950 1950  29737.50         2      1     1     903.6    877.3   1025.1
1975 1975  30504.49         2      1     1     838.0    804.6    919.7
2000 2000  31281.25         2      1     1     625.0    618.5    807.5
2025 2025  32067.77         2      1     1     899.7    884.1    882.1
2050 2050  32864.06         2      1     1     736.4    641.4    857.1
2100 2100  34485.94         2      1     1     634.4    633.6    670.2
3000 3000  70359.38         2      1     1     735.8    817.9    904.1
3500 3500  95757.81         2      1     1     736.4    789.6    783.6
4000 4000 125062.50         2      1     1     894.4    832.4    943.6
4500 4500 158273.44         2      1     1     899.7    892.5    870.7
5000 5000 195390.62         2      1     1     904.0    920.4   1015.3
5500 5500 236414.06         2      1     1     870.6    909.9    936.3
6000 6000 281343.75         2      1     1     823.3    732.4    837.1
