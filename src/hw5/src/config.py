class Config:
    def __init__(self):
        #! mutual
        # self.basedir = "/home/11278041/11278041/frcnn_chicken_1"
        self.basedir = "/home/lab353/Documents/GitHub/PRML_Code/src/hw5/frcnn_chicken_1"
        #! xml_to_csv.py
        self.xml_dir = f'{self.basedir}/110-PR/xml'
        self.train_csv = f'{self.basedir}/110-PR/csv/train.csv'
        #! copy_img.py
        # self.train_csv = f'{self.basedir}/110-PR/csv/train.csv'
        self.train_img_dst = f'{self.basedir}/110-PR/images'
        self.test_csv = f'{self.basedir}/110-PR/csv/test.csv'
        self.test_img_dst = f'{self.basedir}/110-PR/images'
        #! annotate.py
        # self.train_csv = f'{self.basedir}/110-PR/csv/train.csv'
        self.test_annotate_img_name = "50.jpg"
        self.test_annotate_img = f'{self.basedir}/110-PR/images/{self.test_annotate_img_name}'
        self.annotate_output = f'{self.basedir}/110-PR/annotate.txt'
        #! train_frcnn.py
        # self.annotate_output = f'{self.basedir}/110-PR/annotate.txt'
        self.train_result_pickle = f'{self.basedir}/train_result/config.pickle'
        self.train_result_model = f'{self.basedir}/train_result/model_frcnn.hdf5'
        #! test_frcnn.py
        self.test_test_images = f'{self.basedir}/test_images'
        # self.train_result_pickle = f'{self.basedir}/train_result/config.pickle'
        self.test_test_result = f'{self.basedir}/test_result'