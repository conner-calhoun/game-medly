import h2d.Graphics;
import h2d.Text;

typedef Node = {
	x:Float,
	y:Float
}

class Game extends hxd.App {
	public static var inst:Game;

	var hello:h2d.Text;
	var time:Float;
	var g:h2d.Graphics;

	/**
	 * Calculate a sine wave over time
	 * @param x X Coordinate
	 * @param t Time Value
	 * @param a Amplitude
	 * @param f Frequency
	 * @param s Speed
	 * @return Float Y Value
	 */
	function sin(x:Float, t:Float, a:Int, f:Int, s:Int):Float {
		return (a * Math.sin((x + t * s) / f));
	}

	function drawWavyLine(startX:Float, startY:Float, len:Int, t:Float) {
		var x = startX;
		var y = startY;
		var dist = 1;

		g.beginFill(0xFF00FF);
		for (_ in 0...len) {
			y = startY;
			y = y + (sin(x, t, 6, 20, 35) + sin(x, t, 5, 17, 45) + sin(x, t, 4, 15, 40));
			g.drawCircle(x, y, 1);
			x += dist;
		}

		trace(x);

		g.endFill();
	}

	/**
	 * Called once at startup
	 */
	override function init() {
		// for loading sprites
		hxd.Res.initEmbed();
		s2d.scaleMode = AutoZoom(320, 180);

		g = new h2d.Graphics(s2d);

		hello = new h2d.Text(hxd.res.DefaultFont.get(), s2d);
		hello.text = "Heaps Jelly";
		hello.setPosition(5.0, 5.0);
		time = 0.0;
	}

	/**
	 * Called once per frame
	 * @param dt time since last frame
	 */
	override function update(dt:Float) {
		g.clear();

		time += dt;
		drawWavyLine(10, 90, 300, time);
	}

	/**
	 * Entry function
	 */
	public static function main() {
		inst = new Game();
	}
}
