var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
    imagePath: {type: String},
    title: {type: String, required: true},
    description: {type: String, required: true},
    price: {type: Number, required: true},
    category:{type: String, required: true},
    quantity: {type: Number, required: true},
    author: {type: String, required: true},
    publisher: {type: String, required: true},
    status: {type: String, required: true}
});

module.exports = mongoose.model('Product', schema);