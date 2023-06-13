import numpy as np

class Line:
  def __init__(self, a, b):
    self.a = a
    self.b = b

def nearestOutliers(data, model):
  nearest_outliers = list(map(lambda x: np.array([np.abs(model.a * x[0] - x[1] + model.b), x[0], x[1]]), data))
  nearest_outliers = np.array(nearest_outliers)
  sorted_outliers = nearest_outliers[nearest_outliers[:, 0].argsort()][:,1:]
  return sorted_outliers

data = np.array([
  [0,0],
  [1,1],
  [2,0],
  [3,3],
  [4,0],
])

model = Line(0, 2)

b = nearestOutliers(data, model)
print(b)