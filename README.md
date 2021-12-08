# CompConc_Lab03

10⁵ 
Tempo sequencial:   0.002980
Tempo concorrente:  0.003493 com 1 thread
Tempo concorrente:  0.001932 com 2 threads
Tempo concorrente:  0.001347 com 4 threads

10⁷
Tempo sequencial:   0.116947
Tempo concorrente:  0.135637 com 1 thread
Tempo concorrente:  0.073260 com 2 threads
Tempo concorrente:  0.030519 com 4 threads

10⁸
Tempo sequencial:   1.177067
Tempo concorrente:  1.194019 com 1 thread
Tempo concorrente:  0.595649 com 2 threads
Tempo concorrente:  0.293734 com 4 threads

Todos são os menores valores encontrados, foram testados 5 vezes.

Cálculo de ganho de desenpenho:

10⁵
1 thread - 0.002980/0.003493 = 0.85
2 threads- 0.002980/0.001932 = 1.54
4 threads- 0.002980/0.001347 = 2.21

10⁷
1 thread - 0.116947/0.135637 = 0.86
2 threads- 0.116947/0.073260 = 1.59
4 threads- 0.116947/0.030519 = 3.83


10⁸
1 thread - 1.177067/1.194019 = 0.98
2 threads- 1.177067/0.595649 = 1.97
4 threads- 1.177067/0.293734 = 4.00

