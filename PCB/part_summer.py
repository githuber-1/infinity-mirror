import csv
import pprint as pp

part_dict = {}

def main():
    with open('infinity_mirror_v1.0/BoM_V1.0.0.csv') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if row[6] != '' and row[6] != 'Part Number':
                qnt =  int(row[4])
                pn = row[6]
                # if pn is already in the dictionary,update it with new quantity
                if pn in part_dict.keys():
                    prev_qnt = part_dict[pn]
                    new_qnt = prev_qnt + qnt
                    part_dict[pn] = new_qnt
                # if pn is not in dictionary, add it
                else:
                    part_dict[pn] = qnt
    
    pp.pprint(part_dict)


if __name__ == "__main__":
    main()    
