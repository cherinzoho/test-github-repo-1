"""Unit tests for src/utils/helpers.py"""

from __future__ import annotations

import pytest


def test_format_joint_angles_basic() -> None:
    from src.utils.helpers import format_joint_angles

    result = format_joint_angles([0.0, 1.5707, -1.5707])
    assert result == "0.000, 1.571, -1.571"


def test_format_joint_angles_empty() -> None:
    from src.utils.helpers import format_joint_angles

    assert format_joint_angles([]) == ""


def test_load_config_missing_path(tmp_path: pytest.TempPathFactory) -> None:
    from src.utils.helpers import load_config

    result = load_config(str(tmp_path / "nonexistent"), defaults={"key": "value"})
    assert result == {"key": "value"}
