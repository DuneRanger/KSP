#!/usr/bin/env python3
import argparse

import numpy as np
import sklearn.datasets
import sklearn.model_selection as ms
from sklearn.linear_model import LinearRegression
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import PolynomialFeatures

parser = argparse.ArgumentParser()

list_to_int = lambda s: [int(item) for item in s.split(',')]

parser.add_argument("--test_size", default=0.5, type=float, help="Velikost testovací množiny")
parser.add_argument('--one_hot', default=[], help="Index sloupců, kde má být použit one-hot encoder (číslujeme od 0)",
                    type=list_to_int)
parser.add_argument('--standard_scaler', default=[], help="Index sloupců, kde má být použit standard_scaler encoder (číslujeme od 0)",
                    type=list_to_int)
parser.add_argument('--polynomial_features', default=2, type=int, help="Maximální stupeň polynomiálních feature")
parser.add_argument("--seed", default=42, type=int, help="Náhodný seed")


def main(args: argparse.Namespace) -> tuple[np.ndarray, np.ndarray]:
    # Načtení datasetu
    dataset = sklearn.datasets.load_diabetes()
    data = dataset.data
    target = dataset.target
    # TODO: Rozdělte dataset na trénovací a testovací část. Funkci z knihovny sklearn
    # předejte argumenty `test_size=args.test_size, random_state=args.seed`.
    train_data, test_data = ms.train_test_split(data, test_size=args.test_size, random_state=args.seed)
    train_target, test_target = ms.train_test_split(target, test_size=args.test_size, random_state=args.seed)

    # TODO: Podle argumentů použijte one-hot encoder a standard_scaler
    # na jednotlivé sloupce datasetu.
    # Nejdříve transformujte všechny sloupce, které mají být one-hot
    # a poté všechny sloupce, které mají být standard_scaler.
    # Featury na které se nic nepoužívá nechte beze změny.
    # Tedy výsledné featury budou v tomto pořadí:
    # [ one-hot featury , standard_scaler featury , featury beze změny ]
    passthrough = [True for x in range(len(train_data[0]))]
    for x in args.one_hot:
        passthrough[x] = False
    for x in args.standard_scaler:
        passthrough[x] = False
    passthrough_inds = []
    for x in range(len(passthrough)):
        if passthrough[x]: passthrough_inds.append(x)
    ct = ColumnTransformer([
        # název transformace, transformace, sloupce
        ('onehot', OneHotEncoder(), args.one_hot),
        ('standard', StandardScaler(), args.standard_scaler),
        ('passthrough', 'passthrough', passthrough_inds)
    ])
    ct.fit(train_data)
    train_data = ct.transform(train_data)

    # TODO: Vytvořte polynomial featury přes všechny sloupce, do stupně args.polynomial_features
    # dané metodě dejte parametr include_bias=False, aby nepřidávala sloupec, kde je vždy 1
    model = Pipeline([
        ('poly', PolynomialFeatures(args.polynomial_features, include_bias=False)),
        ('reg', LinearRegression())
    ])

    # Doporučuji použít `sklearn.pipeline.make_pipeline` nebo `sklearn.pipeline.Pipeline`
    # pro pohodlnější používání.


    # TODO: Natrénujte transfomery (pipeline) a transformujte pomocí nich testovací data.
    # Metodu 'fit' či `fit_transform` lze zavolat bez výstupních (target) dat, pokud
    # je žádný transformer/model nepotřebuje.
    model.fit(train_data, train_target)
    new_test_data = ct.transform(test_data)
    model.predict(new_test_data)

    return test_data, new_test_data


def print_test_data(test_data):
    for line in range(2):
        print(" ".join("{:.4f}".format(test_data[line, column]) for column in range(test_data.shape[1])))


if __name__ == "__main__":
    args = parser.parse_args()
    main(args)
    prev_test_data, new_test_data = main(args)

    print("Original data:")
    print_test_data(prev_test_data)
    print("Transformed data:")
    print_test_data(new_test_data)