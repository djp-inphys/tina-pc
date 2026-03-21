import click

from .commands import image as image_cmds


@click.group()
def cli():
    """TINA command-line interface."""
    pass


cli.add_command(image_cmds.image)
