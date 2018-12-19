var Product = require('../models/product');

var mongoose = require('mongoose');

mongoose.connect('localhost:27017/shopping');

var products = [
	new Product({
		imagePath: "https:/ebook.vn/uploads/books/Search%20Inside%20Yourself.jpg",
    	title: 'Inside yourself',
    	description: 'This book will open your mind',
    	price: 20,
    	category:'SelfHelp',
    	quantity: 100,
    	author: 'Chade-Meng Tan',
    	publisher: 'Thai Ha',
    	status: 'Published'
	}),

	new Product({
		imagePath: "https:/ebook.vn/uploads/books/Search%20Inside%20Yourself.jpg",
    	title: 'Inside yourself',
    	description: 'This book will open your mind',
    	price: 20,
    	category:'SelfHelp',
    	quantity: 100,
    	author: 'Chade-Meng Tan',
    	publisher: 'Thai Ha',
    	status: 'Published'
	}),

	new Product({
		imagePath: "https:/ebook.vn/uploads/books/Search%20Inside%20Yourself.jpg",
    	title: 'Inside yourself',
    	description: 'This book will open your mind',
    	price: 20,
    	category:'SelfHelp',
    	quantity: 100,
    	author: "Chade-Meng Tan",
    	publisher: 'Thai Ha',
    	status: 'Published'
	})

];

var done = 0;
for (var i = 0; i < products.length; i++) {
    products[i].save(function(err, result) {
        done++;
        if (done === products.length) {
            exit();
        }
    });
}

function exit() {
    mongoose.disconnect();
}