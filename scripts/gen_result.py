from subprocess import run
import os

result_dir = 'results'

ds = {
    'graph_1': 'data/graph_1.txt',
    'graph_2': 'data/graph_2.txt',
    'graph_3': 'data/graph_3.txt',
    'graph_4': 'data/graph_4.txt',
    'graph_5': 'data/graph_5.txt',
    'graph_6': 'data/graph_6.txt',
    'ibm': 'data/ibm.txt',
}

res = [
    ('HITS_authority', 'authority'),
    ('HITS_hub', 'hubness'),
    ('PageRank', 'pagerank'),
    ('SimRank', 'simrank'),
]

if not os.path.exists(result_dir):
    os.mkdir(result_dir)

for data, dpath in ds.items():
    for name, cmd in res:
        run(['build/src/linkanalysis', dpath, os.path.join(result_dir, f'{data}_{name}.txt'), cmd])
