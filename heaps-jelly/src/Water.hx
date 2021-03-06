import Constants;
import JellyMath;

class Water extends h2d.Object {
	var time:Float;
	var g:h2d.Graphics;

	function drawWater(x:Int, y:Int, w:Int, h:Int) {
		g.beginFill(Constants.Palette.Blue);
		g.lineStyle(0, Constants.Palette.LightBlue);

		var len = x + w;
		var sy = 0.0;

		for (i in x...len + 1) {
			var dx = i;

			var sinSum = (JellyMath.sin(time, i / len, 1.2, 12, 1.23) + JellyMath.sin(-time, i / len, 3.1, 30, 0.75)
				+ JellyMath.sin(time, i / len, 2.1, 10, 1.0));

			var dy = y + sinSum;

			if (dx == x)
				sy = dy;

			g.lineTo(dx, dy);
		}

		g.lineTo(len, y + h); // bottom right
		g.lineTo(x, y + h); // bottom left
		g.lineTo(x, sy); // to start

		g.endFill();
	}

	public function init() {
		time = 0.0;
		g = new h2d.Graphics(getScene());
	}

	public function update(dt:Float, x:Int, y:Int, w:Int, h:Int) {
		time += dt;
		g.clear();
		drawWater(x, y, w, h);
	}
}
