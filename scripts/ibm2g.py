import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-d','--data',type=str,required=True)
parser.add_argument('-o','--out',type=str,required=True)
args = parser.parse_args()
open(args.out,'w').writelines([','.join(l.split()[1:])+'\n' for l in open(args.data).readlines()])