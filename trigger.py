import click
import pyutils

@click.argument("-c,--config")
def main(config):
  click.echo(config)


if __name__ == "__main__":
  main()
