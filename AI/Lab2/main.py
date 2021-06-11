from ImageDatabase import ImageDatabase
from Neuron import Neuron

csv = 'pictures/labels.csv'
test_csv = 'pictures/test_labels.csv'
image_database = ImageDatabase(csv)
test_images = ImageDatabase(test_csv)
# print(image_database.__getitem__(4))
# print(image_database.get_data())
neuron = Neuron(image_database, [{'horizontal double': 0},
                              {'horizontal one':    1},
                              {'vertical double':   2},
                              {'vertical one':      3}], 10000, 0.001, 0.9, 0.0000001)
neuron.training()
neuron.check(test_images_database=test_images)
