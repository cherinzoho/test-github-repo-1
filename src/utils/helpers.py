"""BAD Python — intentionally violates ruff rules.
Used ONLY to test that the pre-commit ruff hook catches these.
DO NOT commit this file without fixing — ruff --fix will correct most of these.

Violations introduced:
  E501  — lines over 100 characters
  F841  — unused variable
  E711  — comparison to None using == instead of is
  B006  — mutable default argument
  I001  — unsorted imports
"""

from __future__ import annotations

import os
import sys
import json  # noqa: F401 — intentionally unused import (F401)
from pathlib import Path

def load_config(path: str, defaults: dict = {}):  # B006: mutable default arg
    """Load config from path, merging with defaults."""
    unused_variable = "this is never used"  # F841: unused variable
    full_path = Path(path) / "config.toml"
    if full_path == None:  # E711: use 'is None' not '== None'
        return defaults
    # E501: this line is intentionally way too long to trigger the line-length check from ruff linting rules applied to this file
    return {"path": str(full_path), "platform": os.getenv("PLATFORM", "unknown"), "version": sys.version}


def format_joint_angles(angles: list[float]) -> str:
    return ", ".join(f"{a:.3f}" for a in angles)
