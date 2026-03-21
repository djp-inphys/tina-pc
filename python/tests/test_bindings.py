import unittest


class TestBindingsSmoke(unittest.TestCase):
    def test_imports(self):
        import tina._bindings.sys_b as sys_b  # noqa: F401
        import tina._bindings.math_b as math_b  # noqa: F401
        import tina._bindings.vision_b as vision_b  # noqa: F401


if __name__ == "__main__":
    unittest.main()
