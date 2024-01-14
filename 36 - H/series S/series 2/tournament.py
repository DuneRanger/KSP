#!/usr/bin/env python3
import argparse
import lzma
import os
import pickle
import sys
import urllib.request

import numpy as np
from sklearn.linear_model import Ridge
from sklearn.linear_model import RidgeCV
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import PolynomialFeatures

class Dataset:
    """Dataset půjčovny kol

    Dataset obsahuje tyto informace:
    -0 Hodina - hodina v rámci dne
    -1 Teplota - ve stupních Celsia
    -2 Vlhkost vzduchu - %
    -3 Rychlost větru - m/s
    -4 Viditelnost - v jednotkách 10m
    -5 Rosný bod - ve stupních Celsia
    -6 Sluneční záření - MJ/m^2
    -7 Množství srážek - mm
    -8 Výška sněhové pokrývky - cm
    -9 Roční období - (0: zima, 1: jaro, 2: léto, 3: podzim)
    -10 Prázdniny - (0: ne, 1: ano)
    -11 Fungoval systém - (0: ne, 1: ano)
    -12 Den   - 1-31
    -13 Měsíc - 1-12
    -14 Rok   - 2017 nebo 2018

    Cílová proměnná je počet půjčených kol v dané hodině.
    """
    def __init__(self,
                 name="dataset36-2-S.npz",
                 url="https://ksp.mff.cuni.cz/h/ulohy/36/36-2-S/competition-datasets/"):
        if not os.path.exists(name):
            print("Downloading dataset {}...".format(name), file=sys.stderr)
            urllib.request.urlretrieve(url + name, filename=name)

        # načtení serialovaného datasetu
        dataset = np.load(name, allow_pickle=True)

        self.train_data = dataset['train_data']
        self.test_data = dataset['test_data']
        self.train_target = dataset['train_target']
        # pozor: obsahuje vektor -1
        self.test_target = dataset['test_target']


parser = argparse.ArgumentParser()

parser.add_argument("--seed", default=42, type=int, help="Random seed")


def main(args):
    # nastavení seedu
    np.random.seed(args.seed)

    # načtení datasetu
    dataset = Dataset()
    print(dataset.train_data)

    ct = ColumnTransformer([
        # název transformace, transformace, sloupce
        ('onehot', OneHotEncoder(), [0,9,10,11,12,13,14]),
        ('standard', StandardScaler(), [4,7,8]),
        ('passthrough', 'passthrough', [1,2,3,5,6])
    ])

    ct.fit(dataset.train_data)
    dataset.train_data = ct.transform(dataset.train_data)
    dataset.test_data = ct.transform(dataset.test_data)

    print(dataset.train_data)
    # TODO: Natrénujte model
    model = Pipeline([
        ('poly', PolynomialFeatures(2)),
        ('ridge', Ridge(alpha=0.2))
    ])
    model.fit(dataset.train_data, dataset.train_target)

    # # Pokud si budete chtít uložit model (nebo celou pipeline),
    # # se vám může hodit toto:
    # with lzma.open("competition.model", "wb") as model_file:
    #     pickle.dump(model, model_file)

    # # Poté načtení modelu uděláte takto:
    # with lzma.open("competition.model", "rb") as model_file:
    #     model = pickle.load(model_file)

    pred = model.predict(dataset.test_data)

    with open("36-2-S-prediction.txt", "w") as prediction_file:
        for p in pred:
            print(p, file=prediction_file)


if __name__ == "__main__":
    args = parser.parse_args()
    main(args)