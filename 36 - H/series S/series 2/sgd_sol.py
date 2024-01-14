#!/usr/bin/env python3
import argparse

import numpy as np
import sklearn.datasets
import sklearn.model_selection as ms
import sklearn.linear_model as lm
import sklearn.metrics as mets

parser = argparse.ArgumentParser()

parser.add_argument("--learning_rate", default=0.01, type=float, help="Learning rate")
parser.add_argument("--l2", default=0.0, type=float, help="Síla L2 regularizace")
parser.add_argument("--epochs", default=50, type=int, help="Počet epoch na trénování Minibatch SGD")
parser.add_argument("--batch_size", default=10, type=int, help="Velikost batche")
parser.add_argument("--data_size", default=100, type=int, help="Velikost datasetu")
parser.add_argument("--test_size", default=0.5, type=float, help="Velikost testovací množiny")
parser.add_argument("--seed", default=42, type=int, help="Náhodný seed")
parser.add_argument("--plot", action='store_true', help="Vykreslit predikce")

def main(args: argparse.Namespace):
    # Nastavení seedu generátoru náhodných čísel
    generator = np.random.RandomState(args.seed)

    # Vytvoření náhodného datasetu na regresní úlohu
    data, target = sklearn.datasets.make_regression(n_samples=args.data_size, random_state=args.seed)

    # Přidání sloupce jedniček pro bias
    data = np.concatenate([data, np.ones([args.data_size, 1])], axis=1)
    # print(data)

    # TODO: Rozdělte dataset na trénovací a testovací část, funkci z knihovny sklearn
    # předejte argumenty `test_size=args.test_size, random_state=args.seed`
    
    train_data, test_data = ms.train_test_split(data, test_size=args.test_size, random_state=args.seed)
    train_target, test_target = ms.train_test_split(target, test_size=args.test_size, random_state=args.seed)

    # Vytvoření náhodných vah
    weights = generator.uniform(size=train_data.shape[1])

    train_rmses, test_rmses = [], []
    for epoch in range(args.epochs):
        # TODO: Pro každou epochu náhodně zamíchejte trénovací množinu.
        # Na zamíchání použijte generator.permutation, které vrátí náhodnou permutaci
        # čísel od 0 do počtu prvků v množině.
        # Nemíchejte původní trénovací dataset, ale jen jeho kopii, tedy
        # `train_data` zůstane nezměněný přes všechny epochy.
        random_arr = generator.permutation(len(train_data))
        # print(random_arr)
        # print(len(weights), len(train_data[0]))

        # TODO: Pro každou batch s velikostí args.batch_size spočítejte gradient
        # a upravte váhy. Pokud je args.l2 nenulové, tak upravte váhy i s l2 regularizací.
        # Můžete předpokládat, že args.batch_size je dělitelem počtu prvků v trénovací množině.
        for batch in range(0, len(train_data), args.batch_size):
            descent = [0] * len(weights)
            predictions = []
            new_weights = []
            for i in range(args.batch_size):
                prediction = 0
                for j in range(len(weights)):
                    prediction += train_data[random_arr[batch+i]][j]*weights[j]
                predictions.append(prediction)
            for i in range(args.batch_size):
                gradient_single = 0
                for j in range(len(weights)):
                    descent[j] += 2 * (predictions[i]-train_target[random_arr[batch+i]])*train_data[random_arr[batch+i]][j]/args.batch_size
                # descent.append(gradient_single/args.batch_size)
            # print(descent, "\n\n\n\n\n\n\n")
            for i in range(len(weights)):
                new_weights.append(weights[i] - args.learning_rate*descent[i] - args.learning_rate*args.l2*2*weights[i])
            weights = new_weights

        # TODO: Na konci každé epochy spočítejte metriku RMSE na trénovací a testovací množině.
        # RMSE metrika se rovná odmocnině z MSE a můžete si funkci ze sklearn.metrics
        # říct, že chcete RMSE metriku.
        # RMSE metriku používáme hlavně proto, že když si budete vykreslovat chybu,
        # tak na grafu nebudou tak obří čísla na y-ové ose.
        predictions_train = []
        for i in range(len(train_data)):
            prediction = 0
            for j in range(len(weights)):
                prediction += weights[j]*train_data[i][j]
            predictions_train.append(prediction)
        train_rmse = mets.mean_squared_error(train_target, predictions_train, squared=False)

        predictions_test = []
        for i in range(len(test_data)):
            prediction = 0
            for j in range(len(weights)):
                prediction += weights[j]*test_data[i][j]
            predictions_test.append(prediction)
        test_rmse = mets.mean_squared_error(test_target, predictions_test, squared=False)

        train_rmses.append(train_rmse)
        test_rmses.append(test_rmse)
        print(f"Epoch {epoch+1}: train = {train_rmse:.8f}, test = {test_rmse:.8f}")

    # TODO: Porovnajte si vaše RMSE na testovací množině s implementací z knihovny sklearn,
    # které se učí explicitně pomocí vzorce. Použijte model `Ridge` s parametrem `alpha=args.l2`
    # a parametrem `fit_intercept=False`, protože bias jsme si přidali ručně.
    estimator = lm.Ridge(alpha=args.l2, fit_intercept=False)
    estimator.fit(train_data, train_target)
    predictions = estimator.predict(test_data)
    test_sklearn_rmse = mets.mean_squared_error(test_target, predictions, squared=False)
    print(f"Sklearn RMSE = {test_sklearn_rmse:.8f}")

    # Vykreslení MSE na trénovací a testovací množině
    if args.plot:
        import matplotlib.pyplot as plt
        # Pro vykreslení grafů je potřeba mít nainstalovanou knihovnu matplotlib
        plt.plot(train_rmses, label="Trénovací chyba (RMSE)")
        plt.plot(test_rmses, label="Testovací chyba (RMSE)")
        plt.legend()
        plt.show()


if __name__ == "__main__":
    args = parser.parse_args()
    main(args)