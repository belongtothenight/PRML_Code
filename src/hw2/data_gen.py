import numpy as np
import matplotlib.pyplot as plt

data_cnt = 1000
data_test_mean = 10.4
data_test_std = 0.5
decimal = 2
bin_cnt = 5

def gen_data(mean, std, size, decimal):
    return np.around(np.random.default_rng().normal(mean, std, size), decimals=decimal)

def gen_plot(arr, bin_cnt, mu, sigma, save=False):
    plt.figure()
    count, bins, ignored = plt.hist(arr, bin_cnt, density=True)
    plt.plot(bins, 1/(sigma*np.sqrt(2*np.pi))*np.exp(-(bins-mu)**2/(2*sigma**2)), linewidth=2, color='r')
    if save == False:
        plt.show()
    else:
        plt.savefig(save)
    plt.clf()

def gen_stat(arr):
    print("Mean: ", np.mean(arr))
    print("Standard Deviation: ", np.std(arr))
    print("Variance: ", np.var(arr))

if __name__ == "__main__":
    data_test = gen_data(data_test_mean, data_test_std, data_cnt, decimal)
    print(data_test)
    np.savetxt("./dataset/data_1.csv", data_test, fmt="%."+str(decimal)+"f")
    print("File written!")
    gen_plot(data_test, bin_cnt, data_test_mean, data_test_std, save="./output/data_1.png")
    print("Plot saved!")
    gen_stat(data_test)
    print("Statistics generated!")

