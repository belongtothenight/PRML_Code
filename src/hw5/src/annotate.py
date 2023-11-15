# importing required libraries
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import patches
from config import Config

config = Config()

train = pd.read_csv(config.train_csv)

fig = plt.figure()

#add axes to the image
ax = fig.add_axes([0,0,1,1])

# read and plot the image
image = plt.imread(config.test_annotate_img)
plt.imshow(image)

# iterating over the image for different objects
for _,row in train[train.filename == config.test_annotate_img_name].iterrows():
    xmin = row.xmin
    xmax = row.xmax
    ymin = row.ymin
    ymax = row.ymax
    
    width = xmax - xmin
    height = ymax - ymin
    
    # assign different color to different classes of objects
    if row.type == 'chicken':
        edgecolor = 'b'

    # add bounding boxes to the image
    rect = patches.Rectangle((xmin,ymin), width, height, edgecolor = edgecolor, facecolor = 'none')
    
    ax.add_patch(rect)

data = pd.DataFrame()
data['format'] = train['filename']

# as the images are in train_images folder, add train_images before the image name3
for i in range(data.shape[0]):
    data['format'][i] = 'train_images/' + data['format'][i]

# add xmin, ymin, xmax, ymax and class as per the format required
for i in range(data.shape[0]):
    data['format'][i] = data['format'][i] + ',' + str(train['xmin'][i]) + ',' + str(train['ymin'][i]) + ',' + str(train['xmax'][i]) + ',' + str(train['ymax'][i]) + ',' + train['type'][i]

data.to_csv(config.annotate_output, header=None, index=None, sep=' ')
