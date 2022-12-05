# Project
A parallel quick sort algorithm based on [oneTBB](https://github.com/oneapi-src/oneTBB).
In the benchmark the implementation is compared against its sequential version (`seq`), and STL version (`std`). The comparison is performed on four integer datasets of size $10^8$. The integers are generated randomly and are in range [0, `max_value`] where the `max_value` is iteratively chosen from $\{ 10^2, 10^4, 10^6, 10^8 \}$. For each of these values the experiments are performed five times with different seeds and then the mean value is calculated. To exclude the dataset creation overhead, a dry run (`io_bench`) is performed and then its running time is subtracted from the other algoritms' results.  

# Results
| `max_value`  | Parallel version speedup |
|--------------|--------------------------|
| 100          | 1.821405                 |
| 10000        | 2.496540                 |
| 1000000      | 3.617161                 |
| 100000000    | 4.636972                 |


<details>
    <summary>Detailed results</summary>

```
                      1        2        3        4        5      Mean       Std
par                                                                              
data_100        1.00906  1.02671  1.01086  1.01177  1.10385  1.032450  0.040533
data_10000      1.62020  1.75825  1.59376  1.60778  1.56259  1.628516  0.075638
data_1000000    1.77925  1.71721  1.73147  1.66689  1.73078  1.725120  0.040174
data_100000000  1.89975  2.17217  2.01566  1.96159  1.87050  1.983934  0.119261
                      1        2        3        4        5      Mean       Std
seq                                                                              
data_100        1.87530  1.89513  1.83280  1.93081  1.86851  1.880510  0.036025
data_10000      4.06112  3.99463  4.03958  4.03801  4.19494  4.065656  0.076197
data_1000000    6.19917  6.48823  6.20429  6.25278  6.05571  6.240036  0.157072
data_100000000  8.97595  8.98946  9.25080  9.44852  9.33250  9.199446  0.210014
                       1         2        3         4        5       Mean       Std
std                                                                                  
data_100         9.43262   9.99873  10.1613   9.63503  10.2057   9.886676  0.338837
data_10000      11.37340  12.07590  11.0189  10.97740  11.1374  11.316600  0.451541
data_1000000    13.30580  13.29300  13.4022  12.80480  12.5809  13.077340  0.362273
data_100000000  13.89190  13.79040  13.6920  14.96450  14.0467  14.077100  0.513128
```

</details>

# Usage 
- `./run_experiments.sh` -- Run experiments & produce results.
- `./run_tests.sh` -- Run algorithm correctness testing.

Python 3.6+ with installed `pandas` library is required for the report processing.

# Experiments environment
- GCC version: g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0.
- OS: Ubuntu 22.04 LTS, Windows Subsystem for Linux (WSL 2).
- Processor: AMD Ryzen 9 5900HS, cores: (4 physical, 8 virtual)