class Point:
    x: float
    y: float
    z: float
    weight: float
    
    def __init__(self, x, y, z, weight=1):
        self.x = x
        self.y = y
        self.z = z
        self.weight = weight
        
    def __str__(self):
        return f"{self.x} {self.y} {self.z} {self.weight}"
