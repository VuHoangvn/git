from nose.tools import *
from bin.app import app
from tools import assert_response

def test_index():
	# check that we get a 303 See Other on the / URL
	resp = app.request("/")
	assert_response(resp, status="303 See Other")
	
	# test your first GET request to /hello
	resp = app.request("/hello")
	assert_response(resp)
	