

//var args = process.argv.slice(2); // read the command line arguments

/**
 * read from pipe
 */

/*process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('data', function(data) {
  process.stdout.write(data);
});*/

const util = require('util');

module.exports.Sorter = function(x) {
	return {
		'name' : function() {
			return 'Sorter';
		}
		,'sort' : x
		,'check' : function(input, output) {
			if(!util.isArray(input) || !util.isArray(output))
				return false;
			if(input.length != output.length)
				return false;
			var i = 0;
			for(i = 1; i < output.length; i++) {
				if(output[i] < output[i-1])
					return false;
			}
			return true;
		}
		,'test' : function() {
			console.log('testing');
			var sample = [12,34,23,3,13,4,2];
			var output = this.sort(sample);
			if(this.check(sample,output)) {
				console.log('successful');
			} else {
				console.log('failed');
			}
			return;
		}
	};
}



