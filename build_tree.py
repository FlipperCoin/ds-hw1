#!/usr/bin/python

import sys
import json

def build_s_rec(js):
    if isinstance(js, int):
        return f"SharedPointer<TreeNode<Int>>(new TreeNode<Int>({js}))"

    k = list(js.keys())[0]
    values = js[k]
    indices = k.split(',')
    if len(indices) == 1:
        small = build_s_rec(values[0])
        big = build_s_rec(values[1])
        return f"SharedPointer<TreeNode<Int>>(new TreeNode<Int>({small},{big},{indices[0]}))"
    if len(indices) == 2:
        small = build_s_rec(values[0])
        mid = build_s_rec(values[1])
        big = build_s_rec(values[2])
        return f"SharedPointer<TreeNode<Int>>(new TreeNode<Int>({small},{mid},{big},{indices[0]},{indices[1]}))"
    if len(indices) == 3:
        small = build_s_rec(values[0])
        mid1 = build_s_rec(values[1])
        mid2 = build_s_rec(values[2])
        big = build_s_rec(values[3])
        return f"SharedPointer<TreeNode<Int>>(new TreeNode<Int>({small},{mid1},{mid2},{big},{indices[0]},{indices[1]},{indices[2]}))"

def build_s(js):
    val = js["root"]
    return f"SharedPointer<TreeNode<Int>> root = {build_s_rec(val)};"

def main():
    if len(sys.argv) != 2:
        exit(1)

    js_fpath = sys.argv[1]

    f = open(js_fpath, 'r')

    js = json.load(f)

    s = build_s(js)

    print(s)

if __name__ == "__main__":
    main()