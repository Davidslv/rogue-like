require 'spec_helper'

module RogueLike
  module Components
    RSpec.describe Room do
      def build(room, structure)
        structure.each_with_index do |row, y|
          row.each_with_index do |tile, x|
            room.set(x: x, y: y, tile: tile)
          end
        end
      end

      def assert_equal_room(room, expected)
        expected.each_with_index do |row, y|
          row.each_with_index do |_column, x|
            expect(
              room.get(x: x, y: y)
            ).to eql expected[y][x]
          end
        end
      end

      # TODO: location: x, y
      let(:room) { described_class.new(width: 5, height: 4) }

      describe '#width' do
        it { expect(room.respond_to?(:width)).to be true }
        it { expect(room.width).to eql(5) }
      end

      describe '#height' do
        it { expect(room.respond_to?(:height)).to be true }
        it { expect(room.height).to eql(4) }
      end

      describe '#create' do
        it 'creates a room with given dimensions' do
          room.create

          expected = [
            %w(- - - - -),
            %w(| . . . |),
            %w(| . . . |),
            %w(- - - - -),
          ]

          assert_equal_room(room, expected)
        end
      end
    end
  end
end
