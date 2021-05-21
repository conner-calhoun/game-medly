import h3d.Vector;
import h2d.Graphics;
import h2d.Text;

@:enum
abstract Palette(Int) {
	var Purple = 0x5e315b;
	var PinkRed = 0xb0305c;
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

	/**
	 * Calculate a cosine wave over time
	 * @param x X Coordinate
	 * @param t Time Value
	 * @param a Amplitude
	 * @param f Frequency
	 * @param s Speed
	 * @return Float Y Value
	 */
	function cos(x:Float, t:Float, a:Float, f:Float, s:Float):Float {
		return (a * Math.cos((x + t * s) / f));
	}

	// TODO: Make length based on start and end point
	function drawWavyLine(startX:Float, startY:Float, len:Int, t:Float) {
		var x = startX;
		var y = startY;
		var dist = 1;

		g.lineStyle(1, cast(Palette.PinkRed, Int));
		for (_ in 0...len) {
			y = startY;
			y = y + (sin(x, t, 6, 15, 55) + sin(x, t, 5, 17, 45) + sin(x, t, 4, 15, 40));
			g.lineTo(x, y);
			x += dist;
		}
		g.endFill();
	}

	function drawWavyCircle(startX:Float, startY:Float, radius:Float, t:Float) {
		var nsegs = Math.ceil(Math.abs(radius * 3.14 * 2 / 4));
		if (nsegs < 3)
			nsegs = 3;

		var angle = Math.PI * 2 / nsegs;
		var dist = 0;

		g.lineStyle(1, cast(Palette.PinkRed, Int));
		for (i in 0...nsegs + 1) {
			var a = i * angle;
			var x = startX;
			var y = startY;
			x = y + (sin(y + dist, t, 5, 5, 5));
			y = x + (sin(x - dist, t, 5, 5, 5));

			if (i >= nsegs / 2) {
				dist -= 1;
			} else {
				dist += 1;
			}

			g.lineTo(x + Math.cos(a) * radius, y + Math.sin(a) * radius);
		}
		g.endFill();
	}

	/**
	 * Called once at startup
	 */
	override function init() {
		// for loading sprites
		hxd.Res.initEmbed();
		s2d.scaleMode = AutoZoom(640, 360);

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
		drawWavyLine(10, 90, 620, time);

		drawWavyCircle(200, 250, 75, time);
	}

	/**
	 * Entry function
	 */
	public static function main() {
		inst = new Game();
	}
}
