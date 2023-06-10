import numpy as np
import pickle
import os

dirname = os.path.dirname(__file__)

def rotate(p, origin, degrees):
  angle = np.deg2rad(degrees)
  R = np.array([
    [np.cos(angle), -np.sin(angle)],
    [np.sin(angle),  np.cos(angle)],
  ])
  o = np.atleast_2d(origin)
  p = np.atleast_2d(p)
  return np.squeeze((R @ (p.T-o.T) + o.T).T)

def pre_clip(coords, origin, view_range):
  x_min = origin[0] - view_range * np.sqrt(2)
  x_max = origin[0] + view_range * np.sqrt(2)
  y_min = origin[1] - view_range * np.sqrt(2)
  y_max = origin[1] + view_range * np.sqrt(2)
  cond_x = np.logical_and(x_min <= coords[:,0], coords[:,0] <= x_max)
  cond_y = np.logical_and(y_min <= coords[:,1], coords[:,1] <= y_max)
  clipped = coords[np.logical_and(cond_x, cond_y)]
  return clipped

def post_clip(coords, origin, view_range):
  x_min = origin[0] - view_range
  x_max = origin[0] + view_range
  y_min = origin[1]
  y_max = origin[1] + view_range
  cond_x = np.logical_and(x_min <= coords[:,0], coords[:,0] <= x_max)
  cond_y = np.logical_and(y_min <= coords[:,1], coords[:,1] <= y_max)
  clipped = coords[np.logical_and(cond_x, cond_y)]
  return clipped

def viewedCoords(dataset, origin=(0,0), degrees=0, view_range=1):
  coords_path = 'coords/' + dataset + '.pickle'
  coords_path = os.path.join(dirname, coords_path)
  with open(coords_path, 'rb') as file:
    coords = pickle.load(file)
  pre_clip_coords   = pre_clip(coords, origin, view_range)
  rot_coords        = rotate(pre_clip_coords, origin, degrees)
  prost_clip_coords = post_clip(rot_coords, origin, view_range)
  return prost_clip_coords
