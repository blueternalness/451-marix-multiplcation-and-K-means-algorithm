import matplotlib.pyplot as plt
import numpy as np

# ==========================================
# 1. INPUT DATA
# ==========================================
labels = ['Naive', 'b=4', 'b=8', 'b=16', 'b=32', 'b=128']
times = [39.34, 17.30, 15.67, 17.99, 18.63, 24.33]      # Seconds
mflops = [436.71, 992.85, 1096.38, 954.89, 922.07, 706.07] # MFLOPS

x_pos = np.arange(len(labels))

# ==========================================
# 2. CREATE PLOT
# ==========================================
fig, ax1 = plt.subplots(figsize=(10, 6))

# Bar Chart for Execution Time (Lower is Better)
color_time = '#1f77b4' # Blue
bars = ax1.bar(x_pos, times, color=color_time, alpha=0.6, label='Execution Time (s)')
ax1.set_xlabel('Configuration', fontsize=12, fontweight='bold')
ax1.set_ylabel('Time (seconds)', color=color_time, fontsize=12, fontweight='bold')
ax1.tick_params(axis='y', labelcolor=color_time)
ax1.set_ylim(0, 45) # Set limit slightly higher than max time for readability

# Line Chart for Performance (Higher is Better)
ax2 = ax1.twinx()
color_perf = '#d62728' # Red
line = ax2.plot(x_pos, mflops, color=color_perf, marker='o', linewidth=2, markersize=8, label='Performance (MFLOPS)')
ax2.set_ylabel('Performance (MFLOPS)', color=color_perf, fontsize=12, fontweight='bold')
ax2.tick_params(axis='y', labelcolor=color_perf)
ax2.set_ylim(0, 1200)

# ==========================================
# 3. ANNOTATIONS & LEGEND
# ==========================================
plt.title('Matrix Multiplication Analysis: Naive vs. Block Size Impact', fontsize=14)
plt.xticks(x_pos, labels)
ax1.grid(axis='y', linestyle='--', alpha=0.5)

# Label MFLOPS on the points
for i, v in enumerate(mflops):
    ax2.text(i, v + 30, f"{v:.0f}", color='#d62728', ha='center', fontweight='bold', fontsize=10)

# Label Time inside the bars
for i, v in enumerate(times):
    ax1.text(i, v / 2, f"{v:.1f}s", color='white', ha='center', fontweight='bold', fontsize=10)

plt.tight_layout()
plt.show()