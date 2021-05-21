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

	function sin(time:Float, angle:Float, speed:Float, freq:Float, amp:Float):Float {
		return (Math.sin(time * speed + angle * freq) * amp);
	}

	// TODO: Make length based on start and end point
	function drawWavyLine(startX:Float, y:Float, len:Int, t:Float) {
		var x = startX;

		g.lineStyle(1, cast(Palette.PinkRed, Int));
		for (i in 0...len) {
			var dx = x + i;

			var sinSum = (sin(t, i / len, 1.2, 25, 5) + sin(t, i / len, 3.1, 20, 4) + sin(t, i / len, 2.2, 32, 7));
			var dy = y + sinSum;

			g.lineTo(dx, dy);
		}
		g.endFill();
	}

	/**
	 * Draws a wavy circle
	 * @param x X Position
	 * @param y Y Position
	 * @param r Radius of circle
	 * @param t Time elapsed
	 */
	function drawWavyCircle(x:Float, y:Float, r:Float, t:Float, fill:Bool = false) {
		var nsegs = Math.ceil(Math.abs(r * 3.14 * 2));
		if (nsegs < 3)
			nsegs = 3;

		var angle = Math.PI * 2 / nsegs;

		g.lineStyle(1, cast(Palette.PinkRed, Int));
		if (fill)
			g.beginFill(cast(Palette.PinkRed));
		for (i in 0...nsegs + 1) {
			var a = i * angle;

			var sinSum = sin(t, a, 2, 5, 5) + sin(t, a, 3, 12, 3) + sin(t, a, 2, 10, 8);

			var dx = x + (r + sinSum) * Math.cos(a);
			var dy = y + (r + sinSum) * Math.sin(a);

			g.lineTo(dx, dy);
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

		drawWavyCircle(400, 230, 90, time);
		drawWavyCircle(120, 230, 90, time, true);
	}

	/**
	 * Entry function
	 */
	public static function main() {
		inst = new Game();
	}
}
