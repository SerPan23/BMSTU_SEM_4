class Point:
    def __init__(self, x, y, derivative, second_derivative) -> None:
        self.x = x
        self.y = y
        self.derivative = derivative
        self.second_derivative = second_derivative

    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y
        self.derivative = None
        self.second_derivative = None
