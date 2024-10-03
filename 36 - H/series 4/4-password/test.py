import subprocess
import datetime
import os

environ = os.environ.copy()
environ['PYTHONIOENCODING'] = 'utf-8'

for x in range(50):

    time = datetime.datetime.now().microsecond
    test = subprocess.run(["python", ".\ksp-klient.py", "run", "36-4-4", "python", "main.py"],
                        capture_output=True, text=True, env=environ, encoding="utf-8")
    print(test.stdout)
    with open("test.txt", "a") as f:
        f.write(test.stdout.split()[-2][:-1])
    # line = input()
    # print(line)

