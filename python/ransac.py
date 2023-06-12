import numpy as np
import math

C = 0.00              # The percent of close data points (inliers) required to assert that the model fits well to the data.
E = 0.10              # A threshold value to determine data points that are fit well by the model (inlier).
T = 100

class Line:
  def __init__(self, a, b):
    self.a = a
    self.b = b

class RansacResult:
  def __init__(self):
    self.bestInliersModel = Line(0.0, 0.0)
    self.bestInliersFit = math.inf
    self.bestInliersQty = 0
    self.bestOutliersModel = Line(0.0, 0.0)
    self.bestOutliersFit = math.inf
    self.bestOutliersQty = 0

rs = RansacResult()

def coefficientOfDetermination(data, model, avg_y):
  ss_res = 0
  ss_tot = 0
  for i in range(len(data)):
    f = model.a * data[i][0] + model.b
    y_f = (data[i][1] - f)
    y_y = (data[i][1] - avg_y)
    ss_res += y_f * y_f
    ss_tot += y_y * y_y
  # r = 1 - (ss_res / ss_tot)  # original coefficient
  r = (ss_res / ss_tot)  # modified coefficient (lower is better)
  return r

def leastSquare(data):
  sx = 0
  sy = 0
  sxy = 0
  sx2 = 0
  n = len(data)
  if(n == 0):
    return Line(math.inf, 0), math.inf
  for i in range(n):
    sx += data[i][0]
    sy += data[i][1]
    sxy += data[i][0] * data[i][1]
    sx2 += data[i][0] * data[i][0]
  avg_y = sy / n
  den = (n * sx2 - sx * sx)
  if(den == 0):
    return Line(math.inf, 0), avg_y
  a = (n * sxy - sx * sy) / den
  b = (sy / n) - a * (sx / n)
  return Line(a, b), avg_y

def checkModel(data, temp):
  global rs
  model, _ = leastSquare(temp)

  inliers = []
  outliers = []
  square2 = E * E * (model.a * model.a + 1.0)
  for k in range(len(data)):
    dist = (model.a * data[k][0] - data[k][1] + model.b)
    if (dist * dist <= square2):
      inliers.append(data[k])
    else:
      outliers.append(data[k])

  if (len(inliers) >= rs.bestInliersQty and len(inliers) >= int(len(data) * C)):
    inliersModel, inlinersAvg_y = leastSquare(inliers)
    inliersFit = coefficientOfDetermination(data, inliersModel, inlinersAvg_y)
    if (inliersFit < rs.bestInliersFit):
      rs.bestInliersModel = inliersModel
      rs.bestInliersFit = inliersFit
      rs.bestInliersQty = len(inliers)
      outliersModel, outlinersAvg_y = leastSquare(outliers)
      outliersFit = coefficientOfDetermination(data, outliersModel, outlinersAvg_y)
      rs.bestOutliersModel = outliersModel
      rs.bestOutliersFit = outliersFit
      rs.bestOutliersQty = len(outliers)

def RANSAC(data):
  global rs
  np.seterr(divide='ignore', invalid='ignore')
  initial_point = np.array([500,0])
  for i in range(min(len(data), T)):
    checkModel(data, [initial_point, data[i]])
  return rs