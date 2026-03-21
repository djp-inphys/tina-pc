import json
import unittest

from click.testing import CliRunner


class TestCliSmoke(unittest.TestCase):
    def setUp(self):
        try:
            from tina.cli.main import cli  # noqa: F401
        except OSError:
            self.skipTest("Shared libraries not built; skipping CLI smoke test")
        self.cli = cli

    def test_cli_help(self):
        runner = CliRunner()
        result = runner.invoke(self.cli, ["--help"])
        self.assertEqual(result.exit_code, 0)
        self.assertIn("tina", result.output.lower())

    def test_image_group_help(self):
        runner = CliRunner()
        result = runner.invoke(self.cli, ["image", "--help"])
        self.assertEqual(result.exit_code, 0)
        self.assertIn("smooth", result.output)

    def test_json_flag_format(self):
        runner = CliRunner()
        # command will fail without valid image; just ensure JSON flag handled when command errors
        result = runner.invoke(self.cli, ["image", "smooth", "missing.png", "--json-output"])
        self.assertNotEqual(result.exit_code, 0)
        # output may not be JSON on failure; just ensure stderr-like text is present
        self.assertTrue(result.output)


if __name__ == "__main__":
    unittest.main()
