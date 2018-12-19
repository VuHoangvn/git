const express = require('express');
const router = express.Router();

const Order = require('../models/order.js');
var User = require('../models/user');

/* GET home page. */
router.get('/', checkAdmin, function (req, res) {
	Order.find().then(function(order){
    res.render('admin/orders', {order: order});
  });
});

router.get('/view/:id', (req, res, next) => {
    var orderId = req.params.id;


    Order.findById(orderId, function(err, order) {
       if (err) {
           return res.redirect('/');
       }
        res.render('admin/order', {
        	title: 'View order',
        	order: order,
        	formatDate: function(dateString) {
            var dateWithOffset = new Date(dateString);
            var dateWithoutOffset = new Date(dateWithOffset.getTime() + dateWithOffset.getTimezoneOffset() * 1000 * 60);
            return dateWithoutOffset.toLocaleDateString();
            }
        })
    });
});

// update order status
router.get('/view/update',  function (req, res) {

    res.render('admin/orders');
});

router.post('/view/update', checkAdmin, (req, res) => {
  Order.update({_id: req.body.order_id}, {$set: {status: req.body.order_status}}, {multi: false}, (err, numReplaced) => {
        if(err){
            console.error(colors.red('Failed to update the published state: ' + err));
            res.status(400).json('Published state not updated');
        }else{
            res.redirect('/admin/order/');
        }
    });
    // Order.update({ id: req.body.order_id},  function(err, order){
    //   if(order === null){
    //     res.redirect('/admin/order')
    //   } else {
    //   order.status = req.body.order_status;

    //   order.save();
    //     req.flash('success_msg', 'Modify Successful');
    //     res.redirect('/admin/order');
    //   }
    //             });
});


module.exports = router;
function checkAdmin(req, res, next){

    if(!req.isAuthenticated()){
      next();
    }else{
      res.redirect('/admin/login');
    }
}