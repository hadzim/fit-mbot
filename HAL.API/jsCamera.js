/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */

function Camera(params){
  var settings = {
      url: params.url + "HAL.API.Camera.Camera",
      username: params.username,
      password: params.password,
  };
  
  
 //methods 
          this.Enable = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "Enable",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.Disable = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "Disable",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoMinEngine = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoMinEngine",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoMaxEngine = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoMaxEngine",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoRelEngine = function(_speed){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoRelEngine",
    		params: {speed: _speed},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoMinServo1 = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoMinServo1",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoMaxServo1 = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoMaxServo1",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoRelServo1 = function(_speed){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoRelServo1",
    		params: {speed: _speed},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoMinServo2 = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoMinServo2",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoMaxServo2 = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoMaxServo2",
    		params: {},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }
        this.GoRelServo2 = function(_speed){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GoRelServo2",
    		params: {speed: _speed},
		onRequest: function (r) {
			//console.log(r);
		},
		onResponse: function (r) {
			//console.log(r);
		},
    		success: function (response) {
    		  jdata = response; //$.parseJSON(response);
		      //return jdata;
    		},
    		fault: function (response, errordata) {
				throw('Failed: ' + response);
    		},
    		error: function (request, status, error) {
    			throw('Failed: ' + error + ')');
    		}
    	});
		
		return jdata; 
        }

}



