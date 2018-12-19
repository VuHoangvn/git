const express = require('express');
const bcrypt = require('bcrypt-nodejs');
const fs = require('fs');
var router = express.Router();
var csrf = require('csurf');
var passport = require('passport');


var Order = require('../models/order');
var Cart = require('../models/cart');
// const multer = require('multer');
// const router = express.Router();

// Admin section
router.get('/', function (req, res, next) {
    var messages = req.flash('error');
    res.render('admin/admin');
});


// var csrfProtection = csrf();
// router.use(csrfProtection);

router.get('/login', function (req, res, next) {
    var messages = req.flash('error');
    res.render('admin/login', { messages: messages, hasErrors: messages.length > 0});
});

router.get('/', isLoggedIn, function (req, res, next) {
    Order.find({user: req.user}, function(err, orders) {
        if (err) {
            return res.write('Error!');
        }
        // var cart;
        // orders.forEach(function(order) {
        //     cart = new Cart(order.cart);
        //     order.items = cart.generateArray();
        // });
        res.render('admin/admin', { orders: orders });
    });
});

router.get('/logout', isLoggedIn, function (req, res, next) {
    req.logout();
    res.redirect('/');
});

// router.use('/', notLoggedIn, function (req, res, next) {
//     next();
// });





router.post('/login', passport.authenticate('local.admin.login', {
    failureRedirect: '/admin/login',
    failureFlash: true
}), function (req, res, next) {
    if (req.session.oldUrl) {
        var oldUrl = req.session.oldUrl;
        req.session.oldUrl = null;
        res.redirect(oldUrl);
    } else {
        res.redirect('/admin');
    }
});

router.get('/signup', function (req, res, next) {
    var messages = req.flash('error');
    res.render('admin/signup', {csrfToken: req.csrfToken(), messages: messages, hasErrors: messages.length > 0});
});

router.post('/signup', passport.authenticate('local.admin.signup', {
    failureRedirect: '/admin/signup',
    failureFlash: true
}), function (req, res, next) {
    if (req.session.oldUrl) {
        var oldUrl = req.session.oldUrl;
        req.session.oldUrl = null;
        res.redirect(oldUrl);
    } else {
        res.redirect('/admin');
    }
});
// const cpUpload = upload.fields([{ name: 'bookimg', maxCount: 1 }, { name: 'contentimg', maxCount: 1 }]);
// router.post('/add-product', checkAdmin, cpUpload, function (req, res) {
// 	req.checkBody('frmProductTitle', 'Name is empty').notEmpty();
// 	req.checkBody('author', 'Author is empty').notEmpty();
//   req.checkBody('company', 'Company is empty').notEmpty();
// 	req.checkBody('price', 'Price must be a number').isInt();
// 	req.checkBody('des', 'Description is empty').notEmpty();
// 	console.log(req.files.bookimg[0].filename);
//   const errors = req.validationErrors();
// 	if (errors) {
// 		const file1 = './public/uploads/' + req.files.bookimg[0].filename;
//     const file2 = './public/uploads/' + req.files.contentimg[0].filename;
// 		  const fs = require('fs');
// 			fs.unlink(file1, function(e){
// 				if(e) throw e;
// 			});
//       fs.unlink(file2, function(e){
// 				if(e) throw e;
// 			});
//   		Cate.find().then(function(cate){
// 			res.render('product/addBook',{errors: errors, cate: cate});
// 		});
// 	} else{
// 		const book = new Book({
// 			name: req.body.frmProductTitle,
// 			bookImage: req.files.bookimg[0].filename,
//       contentImage: req.files.contentimg[0].filename,
// 			category: req.body.cate,
// 			des: req.body.des,
// 			price: req.body.price,
//       author: req.body.author,
// 			pagesNumber: req.body.pagesNumber,
//       company: req.body.company,
//       videoId: req.body.videoId
// 		});

// 		book.save().then(function(){
// 			req.flash('success_msg', 'Add Successful');
// 			res.redirect('/admin/product/add-product');
// 		});
//   }
// });

module.exports = router;

function isLoggedIn(req, res, next) {
    if (req.isAuthenticated()) {
        return next();
    }
    res.redirect('/');
}

function notLoggedIn(req, res, next) {
    if (!req.isAuthenticated()) {
        return next();
    }
    res.redirect('/');
}


