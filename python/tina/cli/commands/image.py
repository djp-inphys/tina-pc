import json
from typing import Optional

import click
import numpy as np
from PIL import Image

from ...tools import image as image_tools


def _load_image(path: str) -> np.ndarray:
    img = Image.open(path).convert("L")
    return np.array(img, dtype=np.float64)


def _save_image(arr: np.ndarray, path: str):
    img = Image.fromarray(arr.astype(np.uint8))
    img.save(path)


@click.group()
def image():
    """Image processing commands."""
    pass


@image.command("smooth")
@click.argument("input_path")
@click.option("--sigma", default=1.5, show_default=True, help="Gaussian sigma")
@click.option("--precision", default=0.01, show_default=True, help="Kernel precision")
@click.option("--output", default=None, help="Optional output image path")
@click.option("--json-output", is_flag=True, help="Emit JSON to stdout")
def smooth_cmd(input_path: str, sigma: float, precision: float, output: Optional[str], json_output: bool):
    """Gaussian smooth an image."""
    arr = _load_image(input_path)
    result = image_tools.gaussian_smooth(arr, sigma=sigma, precision=precision)
    if output:
        _save_image(result, output)
    if json_output:
        click.echo(json.dumps({"status": "ok", "shape": list(result.shape), "output": output}))


@image.command("canny")
@click.argument("input_path")
@click.option("--sigma", default=1.0, show_default=True, help="Gaussian sigma")
@click.option("--precision", default=0.01, show_default=True, help="Gaussian precision")
@click.option("--low", default=0.5, show_default=True, help="Low threshold")
@click.option("--high", default=1.5, show_default=True, help="High threshold")
@click.option("--length-thresh", default=10, show_default=True, help="Minimum edge length")
@click.option("--output", default=None, help="Optional output image path")
@click.option("--json-output", is_flag=True, help="Emit JSON to stdout")
def canny_cmd(input_path: str, sigma: float, precision: float, low: float, high: float,
              length_thresh: int, output: Optional[str], json_output: bool):
    """Detect edges using the Canny detector."""
    arr = _load_image(input_path)
    result = image_tools.canny(arr, sigma=sigma, precision=precision, low=low, high=high, length_thresh=length_thresh)
    if output:
        _save_image(result, output)
    if json_output:
        click.echo(json.dumps({
            "status": "ok",
            "shape": list(result.shape),
            "output": output,
            "sigma": sigma,
            "low": low,
            "high": high,
            "length_thresh": length_thresh,
        }))
