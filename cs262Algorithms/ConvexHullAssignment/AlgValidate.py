import os  
import convexhull
import time
import plotly
print plotly.__version__  # version >1.9.4 required

# from plotly.graph_objs import Scatter, Layout
# plotly.offline.plot({
# "data": [
#     Scatter(x=[1, 2, 3, 4], y=[4, 1, 3, 7])
# ],
# "layout": Layout(
#     title="Graham Scan"
# )
# })
files1 = ['Set_A/A_10.dat', 'Set_A/A_50.dat', 'Set_A/A_500.dat', 'Set_A/A_3000.dat', 'Set_A/A_6000.dat', 'Set_A/A_9000.dat', 'Set_A/A_15000.dat', 'Set_A/A_30000.dat']
times1 = []
print("grahamscan")
for fn in files1:
		totalTime = 0.0
		listPts = convexhull.readDataPts(fn)
		
		startTime = time.time()
		for i in range(0, 3):
			convexhull.grahamscan(listPts)   #with any code for validating your outputs
			# print("--- %s seconds ---" % (time.time() - startTime))
			totalTime += time.time() - startTime
		# print(fn)
		averageTime = totalTime / 3
		# print(averageTime)
		times1.append(averageTime)

files2 = ['Set_B/B_10.dat', 'Set_B/B_50.dat', 'Set_B/B_500.dat', 'Set_B/B_3000.dat', 'Set_B/B_6000.dat', 'Set_B/B_9000.dat', 'Set_B/B_15000.dat', 'Set_B/B_30000.dat']
# print(times)
times2 = []
for fn in files2:
		totalTime = 0.0
		listPts = convexhull.readDataPts(fn)
		
		startTime = time.time()
		for i in range(0, 3):
			convexhull.grahamscan(listPts)   #with any code for validating your outputs
			# print("--- %s seconds ---" % (time.time() - startTime))
			totalTime += time.time() - startTime
		# print(fn)
		averageTime = totalTime / 3
		# print(averageTime)
		times2.append(averageTime)

from plotly.graph_objs import Scatter, Layout
plotly.offline.plot({
"data": [
    Scatter(x=[10, 50, 500, 3000, 6000, 9000, 15000, 30000], y= times1, name = 'Set A'),
    Scatter(x=[10, 50, 500, 3000, 6000, 9000, 15000, 30000], y= times2, name = 'Set B')
],
"layout": Layout(
    title="Graham Scan",
    xaxis = dict(title = 'input size'),
    yaxis = dict(title = 'time (s)')
)
})


files1 = ['Set_A/A_10.dat', 'Set_A/A_50.dat', 'Set_A/A_500.dat', 'Set_A/A_3000.dat', 'Set_A/A_6000.dat', 'Set_A/A_9000.dat', 'Set_A/A_15000.dat', 'Set_A/A_30000.dat']
times1 = []
print("Gift Wrap")
for fn in files1:
		totalTime = 0.0
		listPts = convexhull.readDataPts(fn)
		
		startTime = time.time()
		for i in range(0, 3):
			convexhull.giftwrap(listPts)   #with any code for validating your outputs
			# print("--- %s seconds ---" % (time.time() - startTime))
			totalTime += time.time() - startTime
		# print(fn)
		averageTime = totalTime / 3
		# print(averageTime)
		times1.append(averageTime)

files2 = ['Set_B/B_10.dat', 'Set_B/B_50.dat', 'Set_B/B_500.dat', 'Set_B/B_3000.dat', 'Set_B/B_6000.dat', 'Set_B/B_9000.dat', 'Set_B/B_15000.dat', 'Set_B/B_30000.dat']
# print(times)
times2 = []
for fn in files2:
		totalTime = 0.0
		listPts = convexhull.readDataPts(fn)
		
		startTime = time.time()
		for i in range(0, 3):
			convexhull.giftwrap(listPts)   #with any code for validating your outputs
			# print("--- %s seconds ---" % (time.time() - startTime))
			totalTime += time.time() - startTime
		# print(fn)
		averageTime = totalTime / 3
		# print(averageTime)
		times2.append(averageTime)

from plotly.graph_objs import Scatter, Layout
plotly.offline.plot({
"data": [
    Scatter(x=[10, 50, 500, 3000, 6000, 9000, 15000, 30000], y= times1, name = 'Set A'),
    Scatter(x=[10, 50, 500, 3000, 6000, 9000, 15000, 30000], y= times2, name = 'Set B')
],
"layout": Layout(
    title="Gift Wrap",
    xaxis = dict(title = 'input size'),
    yaxis = dict(title = 'time (s)')
)
})


files1 = ['Set_A/A_10.dat', 'Set_A/A_50.dat', 'Set_A/A_500.dat', 'Set_A/A_3000.dat', 'Set_A/A_6000.dat', 'Set_A/A_9000.dat', 'Set_A/A_15000.dat', 'Set_A/A_30000.dat']
times1 = []
print("Quickhull")
for fn in files1:
		totalTime = 0.0
		listPts = convexhull.readDataPts(fn)
		
		startTime = time.time()
		for i in range(0, 3):
			convexhull.amethod(listPts)   #with any code for validating your outputs
			# print("--- %s seconds ---" % (time.time() - startTime))
			totalTime += time.time() - startTime
		# print(fn)
		averageTime = totalTime / 3
		# print(averageTime)
		times1.append(averageTime)

files2 = ['Set_B/B_10.dat', 'Set_B/B_50.dat', 'Set_B/B_500.dat', 'Set_B/B_3000.dat', 'Set_B/B_6000.dat', 'Set_B/B_9000.dat', 'Set_B/B_15000.dat', 'Set_B/B_30000.dat']
# print(times)
times2 = []
for fn in files2:
		totalTime = 0.0
		listPts = convexhull.readDataPts(fn)
		
		startTime = time.time()
		for i in range(0, 3):
			convexhull.amethod(listPts)   #with any code for validating your outputs
			# print("--- %s seconds ---" % (time.time() - startTime))
			totalTime += time.time() - startTime
		# print(fn)
		averageTime = totalTime / 3
		# print(averageTime)
		times2.append(averageTime)

from plotly.graph_objs import Scatter, Layout
plotly.offline.plot({
"data": [
    Scatter(x=[10, 50, 500, 3000, 6000, 9000, 15000, 30000], y= times1, name = 'Set A'),
    Scatter(x=[10, 50, 500, 3000, 6000, 9000, 15000, 30000], y= times2, name = 'Set B')
],
"layout": Layout(
    title="Quickhull",
    xaxis = dict(title = 'input size'),
    yaxis = dict(title = 'time (s)')
)
})


#
