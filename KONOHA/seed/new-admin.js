var Admin = require('../models/admin');

var mongoose = require('mongoose');

mongoose.connect('localhost:27017/shopping');

var admin = new Admin();
admin.email = "vuhoang2119@gmail.com";
admin.password = admin.encryptPassword("123456");


admin.save();

function exit() {
    mongoose.disconnect();
}