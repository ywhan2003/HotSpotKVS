import matplotlib.pyplot as plt

# 从文件中读取数据
results = []
with open("load_data.txt", "r") as infile:
    for line in infile:
        results.append(list(map(int, line.strip().split())))

X_values = [20, 40, 100]

# 绘制图形
for i, result in enumerate(results):
    plt.plot(range(1, 6), result, label=f"X = {X_values[i]}")

plt.xlabel("Time (minutes)")
plt.ylabel("Number of Loads Processed")
plt.title("Load Processing Over Time")
plt.legend()
plt.grid(True)
plt.savefig("./picture/picture1")
plt.show()