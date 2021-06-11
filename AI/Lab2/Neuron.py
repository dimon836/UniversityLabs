import torch
from torch import nn
from torch import optim


class Neuron:
    def __init__(self, dataset, classes, max_epochs, learning_rate, momentum, loss_accuracy):
        self.model = nn.Sequential(nn.Linear(28 * 28, 256),
                                   nn.ReLU(),
                                   nn.Linear(256, 128),
                                   nn.Sigmoid(),
                                   nn.Linear(128, 64),
                                   nn.Sigmoid(),
                                   nn.Linear(64, 5),
                                   nn.LogSoftmax(dim=1))
        self.loss_method = nn.NLLLoss()
        self.dataset = dataset
        self.classes = classes
        self.max_epochs = max_epochs
        self.learning_rate = learning_rate
        self.momentum = momentum
        self.loss_accuracy = loss_accuracy

    def training(self):
        images = self.dataset.get_data()["image names"]
        types = self.dataset.get_data()["image types"]
        images = images.view(images.shape[0], -1)
        output = self.model(images)
        loss = self.loss_method(output, types)
        loss.backward()
        optimizer = optim.SGD(self.model.parameters(), lr=self.learning_rate, momentum=self.momentum)
        loss_prev = 0
        for e in range(self.max_epochs):
            images = images.view(images.shape[0], -1)
            optimizer.zero_grad()
            output = self.model(images)
            loss = self.loss_method(output, types)
            loss.backward()
            optimizer.step()
            if abs(loss - loss_prev) <= self.loss_accuracy:
                print(f'Epoch N{e} with loss = {loss}')
                break
            loss_prev = loss
            if e % 100 == 0:
                print("Epoch N{0} with loss = {1}".format(e, loss))
        print('Training is ended!')

    def check(self, test_images_database):
        images = test_images_database.get_data()['image names']
        types = test_images_database.get_data()['image types']
        for i in range(len(types)):
            image = images[i].view(1, 784)
            with torch.no_grad():
                output = self.model(image)
            ps = torch.exp(output)
            probability = list(ps.numpy()[0])
            predicted_label = probability.index(max(probability))
            true_label = types.numpy()[i]
            print(f"Recognized: {list(self.classes[predicted_label].keys())[0]} "
                  f"Actual: {list(self.classes[true_label].keys())[0]}")
            # test_images_database.show_image(i, 'Recognized: ' + list(self.classes[predicted_label].keys())[0])
