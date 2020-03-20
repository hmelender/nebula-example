import hmbind
import nmath


def main():
    hmbind.test("Hello world!!!")
    em = hmbind.EntityManager()
    placeholder = em.createEntity("placeholder2", "mdl:system/placeholder.n3", "Examples", nmath.Point(0.0, 3.0, 0.0))
    phMotion = placeholder.createMotionComponent()
    phMotion.setVelocity(nmath.Float4(1.0, 0.0, 0.0, 0.0))
    phMotion.setAngularVelocity(nmath.Float4(0.0, 2.0, 0.0, 0.0))


if __name__ == '__main__':
    main()