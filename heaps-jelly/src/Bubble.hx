import Constants;
import JellyMath;

class Bubble extends h2d.Object {
	var time:Float;

	var g:h2d.Graphics;

	/**
	 * Draws a wavy circle
	 * @param x X Position
	 * @param y Y Position
	 * @param r Radius of circle
	 * @param t Time elapsed
	 */
	function drawWavyCircle(x:Float, y:Float, r:Float, t:Float, fill:Bool = false) {
		var nsegs = Math.ceil(Math.abs(r * 3.14 * 2) / 4);
		if (nsegs < 3)
			nsegs = 3;

		var angle = Math.PI * 2 / nsegs;

		g.lineStyle(1, Constants.Palette.Dark);
		if (fill)
			g.beginFill(Constants.Palette.Dark);
		for (i in 0...nsegs + 1) {
			var a = i * angle;

			var sinSum = JellyMath.sin(t, a, 2.5, 5, 5) + JellyMath.sin(-t, a, 2, 12, 3) + JellyMath.sin(t, a, 3, 10, 6);

			var dx = x + (r + sinSum) * Math.cos(a);
			var dy = y + (r + sinSum) * Math.sin(a);

			g.lineTo(dx, dy);
		}
		g.endFill();
	}

	public function init() {
		time = 0.0;
		g = new h2d.Graphics(getScene());
	}

	public function update(dt:Float, x:Float, y:Float, r:Float) {
		time += dt;
		g.clear();
		drawWavyCircle(x, y, r, time, true);
	}
}
