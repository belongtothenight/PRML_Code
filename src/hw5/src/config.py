class Config:
    def __init__(self):
        # mutual
        self.basedir = "/home/11278041/11278041/frcnn_chicken_1"
        # copy_img.py
        self.train_csv = f'{self.basedir}/110-PR/csv/train.csv'
        self.train_img_dst = f'{self.basedir}/110-PR/images/XXX'
        self.test_csv = f'{self.basedir}/110-PR/csv/test.csv'
        self.test_img_dst = f'{self.basedir}/110-PR/images/XXX'