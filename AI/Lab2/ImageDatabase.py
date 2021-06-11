import csv
import os
import cv2
import torch
import matplotlib.pyplot as plt
import matplotlib.image as mpimg


class ImageDatabase:
    def __init__(self, image_dir):
        self.image_dir = image_dir

    def __len__(self):
        image_data = csv.DictReader(open(self.image_dir))
        count = 0
        for _ in image_data:
            count += 1
        return count

    def get_data(self):
        images_to_return = []
        types_to_return = []
        for i in range(0, self.__len__()):
            images_to_return.append(self.__getitem__(i)["image"])
            types_to_return.append(int(self.__getitem__(i)["type"]))
        images_to_return = torch.tensor(images_to_return).type(torch.FloatTensor)
        images_to_return = images_to_return.view(images_to_return.shape[0], -1)
        types_to_return = torch.tensor(types_to_return)
        names_types_dict = {"image names": images_to_return, "image types": types_to_return}
        return names_types_dict

    def show_image(self, index, title):
        image_data = csv.DictReader(open(self.image_dir))
        count = 0
        image = None
        for row in image_data:
            if count == index:
                image = row
            count += 1
        img_path = os.path.join('pictures/', image["Image name"])
        img = mpimg.imread(img_path)
        plt.title(title)
        plt.imshow(img)
        plt.show()

    def __getitem__(self, index):
        image_data = csv.DictReader(open(self.image_dir))
        count = 0
        image_to_return = None
        for row in image_data:
            if count == index:
                image_to_return = row
                break
            count += 1
        if image_to_return is None:
            return 'Index is incorrect!'
        image_path = os.path.join('pictures/', image_to_return["Image name"])
        image = cv2.bitwise_not(cv2.imread(image_path, 0))
        image_type = image_to_return["Image type"]
        ret_dict = {"image": image, "type": image_type}
        return ret_dict

    def __str__(self):
        image_data = csv.DictReader(open(self.image_dir))
        print('Image Database:')
        for row in image_data:
            print(row)
