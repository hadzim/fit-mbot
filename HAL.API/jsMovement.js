/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */

function Movement(params){
  var settings = {
      url: params.url + "HAL.API.Movement.Movement",
      username: params.username,
      password: params.password,
  };
  
  
 //methods 
          this.Move = function(_speedLeft, 
_speedRight){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "Move",
    		params: {speedLeft: _speedLeft, 
speedRight: _speedRight},
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
        this.Stop = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "Stop",
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
        this.SetPosition = function(_posLeft, 
_posRight){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "SetPosition",
    		params: {posLeft: _posLeft, 
posRight: _posRight},
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
        this.GetStatus = function(){
		var jdata;
    	$.jsonrpcTBS({
    		url: settings.url,
    		username: settings.username,
    		password: settings.password,
    		method: "GetStatus",
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

}



