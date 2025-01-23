import numpy as np
from scipy.signal import butter, filtfilt


# Data loading helper method
def load_data(file_name):
    with open(file_name) as f:
        data = np.array(list(map(lambda e: float(e[:-1]), f.readlines())))
        return data


# Data saving helper method
def save_formatted_data(file_name, *data):
    with open(file_name, "w") as f:
        f.write("time," + ",".join([f"Signal{i+1}" for i in range(len(data))]) + "\n")
        for i, j in enumerate(zip(*data)):
            f.write(f"{i}," + ",".join([str(d) for d in j]) + "\n")


# Removing random noise with simple moving average
def apply_moving_average(data, radius=2):
    ret = np.array(data)
    for i in range(len(data) - 2 * radius):
        ret[i] = sum(data[i - radius : i + radius + 1]) / (2 * radius + 1)

    return ret


# Using Butterworth filter to remove high frequency noise
def low_pass_filter(data):
    # Filter parameters
    cutoff_freq = 100  # Cutoff frequency in Hz
    fs = 4000  # Sampling rate in Hz
    order = 4  # Filter order

    # Create the low-pass filter
    nyq = 0.5 * fs
    normal_cutoff = cutoff_freq / nyq
    b, a = butter(order, normal_cutoff, btype="lowpass")

    # Apply the filter
    return filtfilt(b, a, data)


if __name__ == "__main__":
    data = load_data("lev1_with_noise.csv")
    data1 = apply_moving_average(data, radius=7)
    data2 = low_pass_filter(data1)
    save_formatted_data("formatted_processed_data.csv", data, data1, data2)
